#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QString>
#include <QQuickView>
#include <QGuiApplication>
#include <QDebug>
#include <QTimer>
#include <string>
#include <cstdlib>
#include <QQmlContext>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QElapsedTimer>
#include "comms.h"
#include "pathcontroller.h"
/*! \mainpage Wizualizacja Danych Sensorycznych Drona
 *  Dokumentacja aplikacji wizualizującej odczyty z drona
*/
namespace Ui {
class MainWindow;
}
//! Klasa definiująca główne okno
/*!
 * \brief Klasa zawiera elementy potrzebne do wyświetlania wszystkich elementów głównego okna
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //! Konstruktor klasy okna głównego
    /*!
     * \brief Konstruktor klasy okna głównego
     * \param[in] parent Wskaźnik na klasę nadrzędną okna głównego
     */
    explicit MainWindow(QWidget *parent = nullptr);

    //! Destruktor klasy okna głównego
    /*!
    * \brief Destruktor klasy okna głównego
    */
    ~MainWindow();

private slots:
    //! Slot zlecający wysyłanie komendy z okna konsoli
    /*!
    * \brief Slot zlecający wysyłanie komendy z okna konsoli
    */
    void on_send_button_clicked();
    //! Slot pokazujący okno konfiguracyjne
    /*!
    * \brief Slot pokazujący okno konfiguracyjne
    */
    void on_settings_clicked();

protected slots:
    //! Slot odświeżający elementy graficzne głównego okna
    /*!
    * \brief Slot odświeżający elementy graficzne głównego okna
    * \param[in] data Wskaźnik na strukturę zawierającą przetworzone, gotowe dane do wyświetlenia
    */
    void refresh_data(drone_data *data);
    //! Slot wyświetlający podany status
    /*!
    * \brief Slot wyświetlający podany status
    * \param[in] string Status do wyświetlenia
    */
    void change_status(QString string);

private:
    //! Wskaźnik na element user interface
    Ui::MainWindow *ui;
    //! Wskaźnik na element timera, odmierzającego czas od uruchomienia
    QElapsedTimer *timer;
    //! Minimalna zarejestrowana wartość wysokości
    double min_h=100000;
    //! Maksymalna zarejestrowana wartość wysokości
    double max_h=-100000;
    //! Wskaźnik na element odpowiedzialny za komunikację z portem szeregowym
    Comms *settings=nullptr;
    //! Element klasy odpowiedzialnej za kontrolę przebytej drogi
    PathController controller;
};

#endif // MAINWINDOW_H
