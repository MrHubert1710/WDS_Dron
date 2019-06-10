#ifndef COMMS_H
#define COMMS_H

#include <QDialog>
#include "parser.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

namespace Ui {
class Comms;
}


//! Klasa konfiguracyjna komunikacji
/*!
 * \brief Klasa zawierająca elementy potrzebne do komunikacji z dronem
 */
class Comms : public QDialog
{
    Q_OBJECT

public:
    //! Konstruktor klasy Comms
    /*!
     * \brief Konstruktor klasy Comms zawierający mechanizmy inicjalizacyjne, potrzebne do prawidłowego działania.
     * \param parent Wskaźnik na element zawierający element klasy Comms
     * \param console Wskaźnik na element klasy Console do którego zapisywać będzie dane przychodzące
     */
    explicit Comms(QWidget *parent = nullptr,Console *console = nullptr);
    //! Destruktor klasy Comms
    ~Comms();
signals:
    //! Sygnał wydawany gdy status połączenia się zmienia
    /*!
     * \brief Sygnał wydawany gdy status połączenia się zmienia
     * \param string Nowy stan
     */
    void status_changed(QString string);

private slots:
    //! Slot realizujący ukrycie okienka konfiguracji
    /*!
     * \brief Slot realizujący ukrycie okienka konfiguracji
     */
    void on_pushButton_clicked();
    //! Slot finalizujący połączenie
    /*!
     * \brief Slot łączączenia aplikacji z wybranym portem szeregowym, zmienia stan na połączony gdy otwarcie portu się powiedzie
     */
    void on_connect_button_clicked();
    //! Slot szukający dostępnych portów
    /*!
     * \brief Slot wyszukiwania i wypełniania listy dostępnymi portami
     */
    void on_search_button_clicked();
    //! Slot wybierający port
    /*!
     * \brief Slot wybierania portu z listy
     * \param item Wskaźnik na wybrany element
     */
    void on_dev_list_itemClicked(QListWidgetItem *item);
    //! Slot odczytujący dane z portu szeregowego
    /*!
     * \brief Slot odczytywania informacji z połączonego portu szeregowego
     */
    void read_data();
    //! Slot zamykający połączenie
    /*!
     * \brief Slot zamykania portu szeregowego, ustawia stan na rozłączony
     */
    void closeSerialPort();

public slots:
    //! Slot wysyłający dane do portu szeregowego
    /*!
     * \brief Slot wysyłania danych do portu szeregowego
     * \param data Referencja na dane do wysłania
     */
    void write_data(const QByteArray &data);

private:
    //! wskaźnik na user interface
    Ui::Comms *ui;
    //! wskaźnik na powiązaną konsolę
    Console *cons;
    //! lista dostępnych portów szeregowych
    QList<QSerialPortInfo> port_list;
    //! Zaznaczony port szeregowy
    QString selected_port;
    //! Wskaźnik na otwarty port szeregowy
    QSerialPort *serial;
    //! Wskaźnik na element typu parser, dzielący przychodzące wiadomości na użyteczne dane
    parser *parametry;
};

#endif // COMMS_H
