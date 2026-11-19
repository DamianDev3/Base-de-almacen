-- Migracion para bases existentes: agrega el estado de EAN adicional.
-- Ejecutar una sola vez sobre una base que todavia no tenga la columna.
ALTER TABLE EAN_Productos ADD COLUMN es_adicional INTEGER NOT NULL DEFAULT 0;

-- Los EAN existentes que no son principales quedan marcados como adicionales.
UPDATE EAN_Productos
SET es_adicional = CASE WHEN es_principal = 1 THEN 0 ELSE 1 END;

-- Un EAN debe ser principal o adicional, nunca las dos cosas ni ninguna.
CREATE TRIGGER IF NOT EXISTS trg_ean_tipo_insert
BEFORE INSERT ON EAN_Productos
WHEN NEW.es_principal + NEW.es_adicional <> 1
BEGIN
    SELECT RAISE(ABORT, 'El EAN debe ser principal o adicional');
END;

CREATE TRIGGER IF NOT EXISTS trg_ean_tipo_update
BEFORE UPDATE OF es_principal, es_adicional ON EAN_Productos
WHEN NEW.es_principal + NEW.es_adicional <> 1
BEGIN
    SELECT RAISE(ABORT, 'El EAN debe ser principal o adicional');
END;
