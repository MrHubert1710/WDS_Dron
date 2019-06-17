#ifndef PATHCONTROLLER_H
#define PATHCONTROLLER_H

#include <QGeoPath>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

//! Klasa definiująca kontroler drogi
/*!
 * \brief Klasa zawiera elementy potrzebne do przekazywania koordynatów z okna głównego do mapy
 */
class PathController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(
            QGeoPath geopath READ geoPath WRITE setGeopath NOTIFY geopathChanged)

public:
//! Konstruktor klasy definiującej kontroler drogi
/*!
 * \brief Konstruktor klasy definiującej kontroler drogi
 * \param[in] parent Wskaźnik na obiekt nadrzędny
 */
    PathController(QObject *parent = nullptr) : QObject(parent) {}
//! Fukcja dodająca punkt do drogi na mapie
/*!
* \brief Fukcja dodająca punkt do drogi na mapie (usuwa niepotrzebne punkty z tymczasowej ścieżki
* \param[in] lat Szerokość geograficzna
* \param[in] lon Długość geograficzna
*/
    void addPoint(double lat, double lon);
//! Metoda zwracająca ścieżkę tymczasową
/*!
 * \brief Metoda zwracająca ścieżkę tymczasową 
 */
    QGeoPath geoPath() const { return mGeoPath; }
//! Metoda nadpisująca ścieżkę tymczasową
/*!
* \brief Metoda nadpisująca ścieżkę tymczasową (nie sprawdza długości)
* \param[in] geoPath Referencja na strukturę podmieniającą tymczasową ścieżkę
*/
    void setGeopath(const QGeoPath &geoPath);
signals:
//! Sygnał do dodania nowego punktu na mapie
/*!
 * \brief Sygnał do dodania nowego punktu na mapie
 */	
    void geopathChanged();

private:
//! Zmienna przechowywująca ścieżkę tymczasową
/*!
 * \brief Zmienna przechowywująca ścieżkę tymczasową
 */	
    QGeoPath mGeoPath;
};

#endif // PATHCONTROLLER_H
