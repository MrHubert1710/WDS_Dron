#ifndef PARSER_H
#define PARSER_H
#include "ui_mainwindow.h"
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>

//! Struktura przychowywująca pojedyńcze, gotowe dane
/*!
 * \brief Struktura przychowywująca pojedyńcze, gotowe dane
 */
struct drone_data{
    //! Parametr yaw (w stopniach)
    double yaw; // rad
    //! Parametr pitch (w stopniach)
    double pitch; // rad
    //! Parametr roll (w stopniach)
    double roll; // rad
    //! Wysokość (w metrach)
    quint16 height; //m
    //! Naładowanie baterii (Liniowo 0/0% -> 255/100%)
    quint8 battery; //0-255 -> 0%-100%
    //! Prędkość (w metrach na sekundę)
    double speed; //m/s
    //! Długość geograficzna (W-|+E)
    double lon;   // W-|+E
    //! Szerokość geograficzna (S-|+N)
    double lat;   // S-|+N

};
//! Klasa parser odpowiedzialna za przetwarzanie danych
/*!
 * \brief Klasa parser odpowiedzialna za przetwarzanie surowych linii poleceń z portu szeregowego na użyteczne dane
 */
class parser: public QObject
{
Q_OBJECT
public:
    //! Konstruktor klasy parser
    /*!
     * \brief Konstruktor klasy parser, inicializujący tymczasową zmienną tmp
     */
    parser();
signals:
    //! Sygnał emitowany gdy klasa posiada gotowe użyteczne dane
    /*!
     * \brief Sygnał emitowany gdy klasa posiada gotowe użyteczne dane
     * \param present Wskaźnik na strukturę z gotowymi danymi
     */
    void dataChanged(drone_data *present);
public slots:
    //! Slot odpowiedzialny za przetwarzanie surowych danych
    /*!
     * \brief Slot odpowiedzialny za przetwarzanie surowych danych
     * \param line Surowe dane do przetworzenia
     */
    void parseString(QByteArray line);
private:
    //! Tymczasowa zmienna przechowywująca gotowe, użyteczne dane
    drone_data *tmp;
};

#endif // PARSER_H
