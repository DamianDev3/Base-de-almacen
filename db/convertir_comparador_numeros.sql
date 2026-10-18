-- Pasa los campos numericos de la tabla Comparador de texto ("7.499,01")
-- a numeros reales (7499.01). "Cant. precios" queda INTEGER.
-- "Ahorro máximo %" se guarda como valor de porcentaje (0,01% -> 0.01).
CREATE TABLE Comparador_nueva (
    "Código / EAN SEPA" INTEGER,
    "Producto" TEXT,
    "Marca" TEXT,
    "Makro Benavídez" REAL,
    "Yaguar Maschwitz" REAL,
    "Maxiconsumo Pacheco" REAL,
    "Vital El Talar" REAL,
    "Mejor precio" REAL,
    "Mayorista más barato" TEXT,
    "Cant. precios" INTEGER,
    "Diferencia máx.-mín." REAL,
    "Ahorro máximo %" REAL
);

INSERT INTO Comparador_nueva
SELECT
    "Código / EAN SEPA",
    "Producto",
    "Marca",
    CASE WHEN "Makro Benavídez" IS NULL OR TRIM("Makro Benavídez") = '' THEN NULL
         ELSE CAST(REPLACE(REPLACE(TRIM("Makro Benavídez"), '.', ''), ',', '.') AS REAL) END,
    CASE WHEN "Yaguar Maschwitz" IS NULL OR TRIM("Yaguar Maschwitz") = '' THEN NULL
         ELSE CAST(REPLACE(REPLACE(TRIM("Yaguar Maschwitz"), '.', ''), ',', '.') AS REAL) END,
    CASE WHEN "Maxiconsumo Pacheco" IS NULL OR TRIM("Maxiconsumo Pacheco") = '' THEN NULL
         ELSE CAST(REPLACE(REPLACE(TRIM("Maxiconsumo Pacheco"), '.', ''), ',', '.') AS REAL) END,
    CASE WHEN "Vital El Talar" IS NULL OR TRIM("Vital El Talar") = '' THEN NULL
         ELSE CAST(REPLACE(REPLACE(TRIM("Vital El Talar"), '.', ''), ',', '.') AS REAL) END,
    CASE WHEN "Mejor precio" IS NULL OR TRIM("Mejor precio") = '' THEN NULL
         ELSE CAST(REPLACE(REPLACE(TRIM("Mejor precio"), '.', ''), ',', '.') AS REAL) END,
    "Mayorista más barato",
    CASE WHEN "Cant. precios" IS NULL OR TRIM("Cant. precios") = '' THEN NULL
         ELSE CAST(REPLACE(REPLACE(TRIM("Cant. precios"), '.', ''), ',', '.') AS INTEGER) END,
    CASE WHEN "Diferencia máx.-mín." IS NULL OR TRIM("Diferencia máx.-mín.") = '' THEN NULL
         ELSE CAST(REPLACE(REPLACE(TRIM("Diferencia máx.-mín."), '.', ''), ',', '.') AS REAL) END,
    CASE WHEN "Ahorro máximo %" IS NULL OR TRIM("Ahorro máximo %") = '' THEN NULL
         ELSE CAST(REPLACE(REPLACE(REPLACE(TRIM("Ahorro máximo %"), '%', ''), '.', ''), ',', '.') AS REAL) END
FROM Comparador;

DROP TABLE Comparador;
ALTER TABLE Comparador_nueva RENAME TO Comparador;
