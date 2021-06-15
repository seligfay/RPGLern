So far, only a simple inventory system has been implemented.     
The I key is responsible for switching widgets between inventory and combat.    
E-collects the item.    
Shift + Drag item - if used on a stack of items, allows you to split the stack.    
Moving an item outside of the inventory will cause it to drop into the world.    
Check the inventory component in character. It must have a DataTable and either a predefined inventory array or the number of cells to set.     
The number of cells is added to the inventory array, so you can use both functions if you need to have items in your inventory when spawning.    