-- Campos de la ficha de producto que faltaban (hoja Base almacen / Alta producto).
ALTER TABLE Productos ADD COLUMN caracteristicas TEXT;
ALTER TABLE Productos ADD COLUMN envase TEXT;
ALTER TABLE Productos ADD COLUMN unidad TEXT;
ALTER TABLE Productos ADD COLUMN observacion TEXT;
