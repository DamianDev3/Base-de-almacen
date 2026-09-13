#include "subCategoria.h"
#include "Categorias.h"
#include "ArchivoSubcategoria.h"
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

subCategoria::subCategoria()
{
    _idSubcategoria = 0;
    strcpy(_nombresubCategoria,"SIN_SUBCATEGORIA");
    _estadoSubcategoria = false;
    _idPadre = 0;
}
subCategoria::subCategoria(int idSub,int idPadre, const char* nombSub,bool estSub)
{
_idSubcategoria = idSub;
strcpy(_nombresubCategoria,nombSub);
_estadoSubcategoria = estSub;
_idPadre = idPadre; 
}
///SETTERS
void subCategoria::setIdSubcategoria(int idSub)
{
    _idSubcategoria = idSub;
}
void subCategoria::setIDpadre(int idBadre)
{
    _idPadre = idBadre;
}

void subCategoria::setnombreSubcategoria(const char* nombreSub)
{
    strcpy(_nombresubCategoria,nombreSub);
}
void subCategoria::setEstadoSubcategoria(bool estadoSub)
{
    _estadoSubcategoria = estadoSub;
}
/// GETTERS

int subCategoria::getIdSubcategoria()
{
    return _idSubcategoria;
}
int subCategoria::getIdPadre()
{
    return _idPadre;
}
const char* subCategoria::getNombreSubcategoria()
{
    return _nombresubCategoria;
}
bool subCategoria::getEstadoSubcategoria()
{
    return _estadoSubcategoria;
}
// Estructura auxiliar solo para inicializar el catálogo base
struct SemillaSubcategoria {
    int idPadre;
    const char* nombre;
};

void subCategoria::mostrarCatalogoInicial()
{
    ArchivoSubcategoria archiSub;

    // Validar que no existan datos anteriormente:
    if (archiSub.contarRegistro() > 0) 
    {
        return;
    };

const SemillaSubcategoria listaBase[] = {
        // 1. Alimentos (17)
        {1, "Aceites y vinagres"}, {1, "Arroz"}, {1, "Pastas"}, {1, "Harinas y premezclas"},
        {1, "Legumbres"}, {1, "Conservas"}, {1, "Salsas y aderezos"}, {1, "Mermeladas y dulces"},
        {1, "Azucar y edulcorantes"}, {1, "Sal y condimentos"}, {1, "Caldos, sopas y pures"},
        {1, "Cereales y desayuno"}, {1, "Galletitas"}, {1, "Snacks"}, {1, "Panificados"},
        {1, "Reposteria y postres"}, {1, "Untables"},

        // 2. Bebidas sin alcohol (7)
        {2, "Aguas"}, {2, "Aguas saborizadas"}, {2, "Gaseosas"}, {2, "Jugos"},
        {2, "Isotonicas y deportivas"}, {2, "Energeticas"}, {2, "Sodas"},

        // 3. Infusiones (4)
        {3, "Yerba mate"}, {3, "Cafe"}, {3, "Te"}, {3, "Cacao y chocolatadas"},

        // 4. Bebidas alcoholicas (6)
        {4, "Cervezas"}, {4, "Vinos"}, {4, "Espumantes"}, {4, "Aperitivos"},
        {4, "Destilados"}, {4, "Bebidas listas para tomar"},

        // 5. Golosinas (8)
        {5, "Alfajores"}, {5, "Chocolates"}, {5, "Caramelos"}, {5, "Chicles"},
        {5, "Pastillas"}, {5, "Gomitas"}, {5, "Turrones"}, {5, "Chupetines"},

        // 6. Lacteos y refrigerados (7)
        {6, "Leches"}, {6, "Yogures"}, {6, "Quesos"}, {6, "Manteca y margarina"},
        {6, "Crema"}, {6, "Postres refrigerados"}, {6, "Fiambres y embutidos"},

        // 7. Frescos (3)
        {7, "Huevos"}, {7, "Frutas y verduras"}, {7, "Panaderia fresca"},

        // 8. Congelados (5)
        {8, "Helados"}, {8, "Vegetales congelados"}, {8, "Papas congeladas"},
        {8, "Comidas preparadas"}, {8, "Carnes y derivados congelados"},

        // 9. Limpieza (14)
        {9, "Lavandina"}, {9, "Detergentes"}, {9, "Lavavajillas"}, {9, "Desinfectantes"},
        {9, "Limpiadores de piso"}, {9, "Limpiadores multiuso"}, {9, "Limpiadores de bano"},
        {9, "Limpieza de cocina"}, {9, "Jabon para ropa"}, {9, "Detergente para ropa"},
        {9, "Suavizantes"}, {9, "Quitamanchas"}, {9, "Esponjas y panos"}, {9, "Insecticidas"},

        // 10. Cuidado personal e higiene (9)
        {10, "Shampoo"}, {10, "Acondicionador"}, {10, "Jabon de tocador"}, {10, "Desodorantes"},
        {10, "Higiene bucal"}, {10, "Afeitado"}, {10, "Higiene femenina"}, {10, "Cuidado corporal"},
        {10, "Cuidado del cabello"},

        // 11. Papel y descartables (7)
        {11, "Papel higienico"}, {11, "Rollos de cocina"}, {11, "Servilletas"}, {11, "Panuelos"},
        {11, "Bolsas de residuos"}, {11, "Papel aluminio y film"}, {11, "Vasos y platos descartables"},

        // 12. Bebes (4)
        {12, "Panales"}, {12, "Toallitas humedas"}, {12, "Cuidado del bebe"}, {12, "Alimentacion infantil"},

        // 13. Mascotas (4)
        {13, "Alimento para perros"}, {13, "Alimento para gatos"}, {13, "Higiene para mascotas"},
        {13, "Accesorios para mascotas"},

        // 14. Hogar y bazar (6)
        {14, "Pilas"}, {14, "Fosforos y encendedores"}, {14, "Velas"}, {14, "Bolsas y recipientes"},
        {14, "Utensilios basicos"}, {14, "Otros articulos de hogar"},

        // 15. Otros (1)
        {15, "Otros"}
    };
    
    int total = sizeof(listaBase) / sizeof(listaBase[0]);

    for (int i = 0; i < total; i++)
    {
         
        int nuevoId = i + 1;
        subCategoria nuevoRegistro(nuevoId, listaBase[i].idPadre, listaBase[i].nombre, true);
        archiSub.guardadoSubCategoria(nuevoRegistro);
    }
    
}