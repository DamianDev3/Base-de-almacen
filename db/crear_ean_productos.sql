-- Relacion entre EAN y producto.
-- Un producto puede tener varios EAN; cada EAN pertenece a un solo producto.
CREATE TABLE IF NOT EXISTS EAN_Productos (
    id_ean       INTEGER PRIMARY KEY AUTOINCREMENT,
    ean          TEXT NOT NULL UNIQUE,
    id_producto  INTEGER NOT NULL,
    es_principal INTEGER NOT NULL DEFAULT 0,
    es_adicional INTEGER NOT NULL DEFAULT 0,
    FOREIGN KEY (id_producto) REFERENCES Productos(id_producto),
    CHECK (es_principal + es_adicional = 1)
);

-- Indice para buscar todos los EAN de un producto.
CREATE INDEX IF NOT EXISTS idx_ean_productos_producto
    ON EAN_Productos(id_producto);

-- Un solo EAN principal por producto.
CREATE UNIQUE INDEX IF NOT EXISTS ux_ean_principal
    ON EAN_Productos(id_producto)
    WHERE es_principal = 1;

-- Migracion: el EAN que hoy tiene cada producto pasa a ser su EAN principal.
INSERT OR IGNORE INTO EAN_Productos (ean, id_producto, es_principal)
SELECT TRIM(eanProductos), id_producto, 1
FROM Productos
WHERE eanProductos IS NOT NULL
  AND TRIM(eanProductos) <> '';
