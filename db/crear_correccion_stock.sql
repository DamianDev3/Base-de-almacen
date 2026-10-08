-- Tabla para la correccion manual de stock.
-- Corresponde a la hoja "Correccion stock(manual)" del Excel "sistema almacen".
-- Los comentarios indican el campo de la clase CorreccionStock que la llena.
CREATE TABLE IF NOT EXISTS Correccion_Stock (
    id_correccion    INTEGER PRIMARY KEY AUTOINCREMENT,  -- _idDeCorreccion / ID correccion
    fecha_hora       TEXT    NOT NULL,                   -- _fechaHora / Fecha-hora
    codigo_interno   INTEGER,                            -- Codigo interno del producto
    ean_leido        TEXT,                               -- _eanProductoCorreccion / EAN leido
    producto         TEXT,                               -- _productoCorregido / Producto (snapshot)
    stock_actual     INTEGER,                            -- _stockActual / Stock actual
    motivo           TEXT,                               -- _motivoCorreccion / Motivo (lista del sistema)
    cantidad         INTEGER,                            -- _cantidadCorregida / Cantidad
    direccion        TEXT,                               -- Direccion del ajuste (SUMA / RESTA)
    stock_resultante INTEGER,                            -- _stockResultante / Stock resultante
    usuario          TEXT,                               -- usuario / Usuario (Administrador o Logistica)
    id_movimiento    INTEGER                             -- _idMovimiento / ID movimiento generado
);
