-- Tabla para el historial automatico de movimientos de stock.
-- Corresponde a la hoja "Movimientos stock(automatica)" del Excel "sistema almacen".
CREATE TABLE IF NOT EXISTS Movimientos_Stock (
    id_movimiento   INTEGER PRIMARY KEY AUTOINCREMENT,  -- ID movimiento
    fecha_hora      TEXT NOT NULL,                      -- Fecha/hora
    codigo_interno  INTEGER,                            -- Codigo interno
    ean_leido       TEXT,                               -- EAN leido
    producto        TEXT,                               -- Producto (snapshot)
    tipo_movimiento TEXT,                               -- Tipo movimiento (lista del sistema)
    motivo          TEXT,                               -- Motivo
    cantidad        INTEGER,                            -- Cantidad
    impacto_stock   INTEGER,                            -- Impacto stock (+suma / -resta)
    usuario         TEXT,                               -- Usuario
    referencia      TEXT                                -- Referencia (venta, correccion, etc.)
);

-- Agrega CORRECCIÓN a la lista de tipos de movimiento (sin duplicarla si ya existe).
UPDATE lista_sistema
SET tipo_movimiento = tipo_movimiento || ',CORRECCIÓN'
WHERE tipo_movimiento IS NOT NULL
  AND tipo_movimiento NOT LIKE '%CORRECCIÓN%';
