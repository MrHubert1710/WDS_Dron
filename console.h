#ifndef CONSOLE_H
#define CONSOLE_H

#include <QTextEdit>
#include <QScrollBar>

//! Klasa symulująca konsolę
/*!
 * \brief Klasa zawiera elementy potrzebne do wyświetlania przychodzących i wychodzących danych w postaci konsoli
 */
class Console : public QTextEdit
{
Q_OBJECT
private:
    //! Zmienna sygnalizująca nową linię poleceń
    bool new_recieve;
public:
    //! Zmienna przetrzymująca ostatnią pełną linię poleceń
    QByteArray last_line;
    //! Konstruktor klasy Console
    /*!
     *  \brief Kostruktor klasy Console inicializujący funkcjonalność konsoli
     *  \param parent Wskaźnik na rodzica zawierającego element klasy konsoli
     */
    Console(QWidget *parent);
    //! Metoda umieszczająca dane na polu konsoli
    /*!
     * \brief Metoda umieszczająca fragmenty danych na widocznym polu konsoli
     * \param data Dane do umieszczenia
     * \param sending Kierunek komunikacji (true dla wysyłania, false dla odbierania)
     */
    void putData(const QByteArray &data,bool sending);
signals:
    //! Sygnał emitowany po odczytaniu znaku nowej linii
    /*!
     * \brief Sygnał emitowany po odczytaniu znaku nowej linii, oznaczający gotowość do odczytu linii poleceń
     * \param dane Linia poleceń do odczytania i interpretacji
     */
    void line_ready(QByteArray dane);
};

#endif // CONSOLE_H
