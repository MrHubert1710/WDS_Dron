#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTimer>
#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <memory>
#include "texturedsphere.h"
//! Klasa definiująca element graficzny OpenGL
/*!
 * \brief Klasa zawiera elementy potrzebne do wyświetlania trójwymiarowego sztucznego horyzontu
 */
class Dialog : public QOpenGLWidget
{
Q_OBJECT
public:
    //! Konstruktor klasy Dialog
    /*!
     * \brief Konstruktor klasy Dialog
     * \param parent Wskaźnik do elementu zawierającego element klasy Dialog
     */
    Dialog(QWidget *parent);

public slots:
    //! Slot obracający sztuczny horyzont do określonej pozycji
    /*!
     * \brief Slot natychmiastowo obracający sztuczny horyzont do określonej pozycji
     * \param yaw Parametr yaw (-180 - 180)
     * \param pitch Parametr pitch (-180 - 180)
     * \param roll Parametr roll (-180 - 180)
     */
    void setRotation(float yaw, float pitch, float roll);
    //! Slot obracający sztuczny horyzont do określonej pozycji na osi Yaw
    /*!
     * \brief Slot natychmiastowo obracający sztuczny horyzont do określonej pozycji na osi Yaw
     * \param yaw Parametr yaw (-180 - 180)
     */
    void setRotationY(float yaw);
    //! Slot obracający sztuczny horyzont do określonej pozycji na osi Pitch
    /*!
     * \brief Slot natychmiastowo obracający sztuczny horyzont do określonej pozycji na osi Pitch
     * \param pitch Parametr pitch (-180 - 180)
     */
    void setRotationP(float pitch);
    //! Slot obracający sztuczny horyzont do określonej pozycji na osi Roll
    /*!
     * \brief Slot natychmiastowo obracający sztuczny horyzont do określonej pozycji na osi Roll
     *  \param roll Parametr roll (-180 - 180)
     */
    void setRotationR(float roll);

protected:
    //! Metoda inicjalizująca struktury OpenGL
    /*!
     * \brief Metoda inicjalizująca struktury OpenGL
     */
    void initializeGL();
    //! Metoda inicjalizująca scenę
    /*!
     * \brief Metoda inicjalizująca scenę
     */
    void paintGL();


private:
    //! Aktualna wartość parametru roll
    float a_roll=0;
    //! Aktualna wartość parametru pitch
    float a_pitch=0;
    //! Aktualna wartość parametru yaw
    float a_yaw=0;
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    QMatrix4x4 m_view;
    QMatrix4x4 m_proj;
    QMatrix4x4 m_model;
    QMatrix4x4 m_model_def;

    QOpenGLShaderProgram m_program;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_cubeVertices;
    QOpenGLBuffer m_cubeIndices;
#endif
    //! Obiekt sztucznego horyzontu
    TexturedSphere m_sphere;

    //! Wskaźnik na teksturę sztucznego horyzontu
    QOpenGLTexture* m_texture;

};

#endif // DIALOG_H
