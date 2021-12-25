// Copyright Epic Games, Inc. All Rights Reserved.

#include "WeeeelCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "WeeelAbilitySystem.h"
#include "WeeelAttributeSet.h"
#include "WeeelGameplayAbility.h"
#include "Components/WidgetComponent.h"
#include "Public/PlayerControllers/MainPlayerController.h"
#include "WeeeelGameMode.h"
#include <GameplayEffectTypes.h>

//////////////////////////////////////////////////////////////////////////
// AWeeeelCharacter

AWeeeelCharacter::AWeeeelCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//ability system
	AbilitySystemComponent = CreateDefaultSubobject<UWeeelAbilitySystem>("AbilitySystemComp");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	FloatingWidget = CreateDefaultSubobject<UWidgetComponent>(FName("UIFloatingStatusBarComponent"));
	FloatingWidget->SetupAttachment(RootComponent);

	Attributes = CreateDefaultSubobject<UWeeelAttributeSet>("Attributes");

	


	//------------------------------

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void AWeeeelCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (AbilitySystemComponent) {
		UFloatingStatusBar* widget = Cast<UFloatingStatusBar>(FloatingWidget->GetWidget());
		if (widget != nullptr) {
			widget->SetHealthPercentage(Attributes->GetHealth() / Attributes->GetMaxHealth());
			widget->SetStaminaPercentage(Attributes->GetStamina() / Attributes->GetMaxStamina());
			widget->SetManaPercentage(Attributes->GetMana() / Attributes->GetMaxMana());
		}
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetHealthAttribute()).AddUObject(this, &AWeeeelCharacter::OnHealthChange);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetStaminaAttribute()).AddUObject(this, &AWeeeelCharacter::OnStaminaChange);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetManaAttribute()).AddUObject(this, &AWeeeelCharacter::OnManaChange);
		//Attributes->onChangeHealth.BindUObject(widget, &UFloatingStatusBar::SetHealthPercentage);
	}
}

void AWeeeelCharacter::OnHealthChange(const FOnAttributeChangeData& Data)
{
	UFloatingStatusBar* widget = Cast<UFloatingStatusBar>(FloatingWidget->GetWidget());
	float procentage = Attributes->GetHealth() / Attributes->GetMaxHealth();
	if (!(procentage > 0)) {
		CallRestartPlayer();
	}
	if (widget != nullptr) {
		widget->SetHealthPercentage(procentage);
	}

}

void AWeeeelCharacter::OnStaminaChange(const FOnAttributeChangeData& Data)
{
	UFloatingStatusBar* widget = Cast<UFloatingStatusBar>(FloatingWidget->GetWidget());
	if (widget != nullptr) {
		widget->SetStaminaPercentage(Attributes->GetStamina() / Attributes->GetMaxStamina());
	}
}

void AWeeeelCharacter::OnManaChange(const FOnAttributeChangeData& Data)
{
	UFloatingStatusBar* widget = Cast<UFloatingStatusBar>(FloatingWidget->GetWidget());
	if (widget != nullptr) {
		widget->SetManaPercentage(Attributes->GetMana() / Attributes->GetMaxMana());
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AWeeeelCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AWeeeelCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AWeeeelCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AWeeeelCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AWeeeelCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AWeeeelCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AWeeeelCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AWeeeelCharacter::OnResetVR);

	if (AbilitySystemComponent && InputComponent) {
		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "EWeeeelAbilityInputID",
			static_cast<int32>(EWeeeelAbilityInputID::Confirm), static_cast<int32>(EWeeeelAbilityInputID::Cancel));
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}


void AWeeeelCharacter::OnResetVR()
{
	// If Weeeel is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in Weeeel.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AWeeeelCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AWeeeelCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AWeeeelCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AWeeeelCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AWeeeelCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AWeeeelCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

//getAbilitySystem

class UAbilitySystemComponent* AWeeeelCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


void AWeeeelCharacter::InitializeAttributes() {
	if (AbilitySystemComponent && DefaultAttributeEffect) {
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);

		if (SpecHandle.IsValid()) {
			FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
		
	}
}

void AWeeeelCharacter::GiveAbilities() {
	if (HasAuthority() && AbilitySystemComponent) {
		for (TSubclassOf<class UWeeelGameplayAbility>& StartupAbility : DefaultAbilities) {
			AbilitySystemComponent->GiveAbility(
				FGameplayAbilitySpec(StartupAbility, 1, static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputId), this)
			);
		}
	}
}

void AWeeeelCharacter::PossessedBy(AController* NewController) {
	Super::PossessedBy(NewController);
	//server GAS Init
	AbilitySystemComponent->InitAbilityActorInfo(this, this);//character as ability owner

	InitializeAttributes();
	GiveAbilities();
}


void AWeeeelCharacter::OnRep_PlayerState() {
	Super::OnRep_PlayerState();

	//client GAS Init
	AbilitySystemComponent->InitAbilityActorInfo(this, this);//character as ability owner
	InitializeAttributes();

	if (AbilitySystemComponent && InputComponent) {
		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "EWeeeelAbilityInputID", 
			static_cast<int32>(EWeeeelAbilityInputID::Confirm), static_cast<int32>(EWeeeelAbilityInputID::Cancel));
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
	

}

float AWeeeelCharacter::GetHealth() const
{
	if (Attributes)
	{
		return Attributes->GetHealth();
	}

	return 0.0f;
}

float AWeeeelCharacter::GetMaxHealth() const
{
	if (Attributes)
	{
		return Attributes->GetMaxHealth();
	}

	return 0.0f;
}

float AWeeeelCharacter::GetMana() const
{
	if (Attributes)
	{
		return Attributes->GetMana();
	}

	return 0.0f;
}

float AWeeeelCharacter::GetMaxMana() const
{
	if (Attributes)
	{
		return Attributes->GetMaxMana();
	}

	return 0.0f;
}

float AWeeeelCharacter::GetStamina() const
{
	if (Attributes)
	{
		return Attributes->GetStamina();
	}

	return 0.0f;
}

float AWeeeelCharacter::GetMaxStamina() const
{
	if (Attributes)
	{
		return Attributes->GetMaxStamina();
	}

	return 0.0f;
}

void AWeeeelCharacter::Destroyed()
{
	Super::Destroyed();
}

void AWeeeelCharacter::CallRestartPlayer()
{
	AMainPlayerController* PCref = Cast<AMainPlayerController>(GetController());
	if (PCref) {
		PCref->ActorHealthIsZero();
	}
	else {
		Destroy();
	}
}
