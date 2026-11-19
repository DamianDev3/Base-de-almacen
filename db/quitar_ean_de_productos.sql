-- Quita la columna eanProductos de Productos: ahora los EAN viven en EAN_Productos.
-- Por seguridad, primero migra cualquier EAN que todavia no este en la tabla nueva.
INSERT OR IGNORE INTO EAN_Productos (ean, id_producto, es_principal)
SELECT TRIM(eanProductos), id_producto, 1
FROM Productos
WHERE eanProductos IS NOT NULL
  AND TRIM(eanProductos) <> '';

CREATE TABLE Productos_nueva (
    id_producto      INTEGER PRIMARY KEY,
    nombreProductos  TEXT NOT NULL,
    MarcaProductos   TEXT,
    variantes        TEXT,
    caracteristicas  TEXT,
    envase           TEXT,
    contenido        TEXT,
    unidad           TEXT,
    unidades_pack    INTEGER DEFAULT 1,
    precio_venta     REAL NOT NULL DEFAULT 0.0,
    stock_minimo     INTEGER DEFAULT 0,
    stock_objetivo   INTEGER DEFAULT 0,
    stock_actual     INTEGER DEFAULT 0,
    id_subcategoria  INTEGER,
    observacion      TEXT
);

INSERT INTO Productos_nueva (
    id_producto, nombreProductos, MarcaProductos, variantes,
    caracteristicas, envase, contenido, unidad, unidades_pack,
    precio_venta, stock_minimo, stock_objetivo, stock_actual,
    id_subcategoria, observacion
)
SELECT
    id_producto, nombreProductos, MarcaProductos, variantes,
    caracteristicas, envase, contenido, unidad, unidades_pack,
    precio_venta, stock_minimo, stock_objetivo, stock_actual,
    id_subcategoria, observacion
FROM Productos;

DROP TABLE Productos;
ALTER TABLE Productos_nueva RENAME TO Productos;
