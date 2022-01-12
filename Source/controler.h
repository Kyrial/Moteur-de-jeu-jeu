#ifndef CONTROLER_H
#define CONTROLER_H


#include <QOpenGLWidget>
#include <QObject>
#include <QKeyEvent>

class Controler : public QOpenGLWidget
{
    Q_OBJECT

public:
    /**
     * @brief Gère les touches
     */
    Controler();

public slots:
    /**
     * @brief evenement lorsque une touche du clavier est  préssée
     * @param event
     */
    void keyPressEvent(QKeyEvent *event);
    /**
     * @brief evenement lié au mouvement de la souris
     * @param event
     */
    void mouseMoveEvent(QMouseEvent *event);

signals:
    /**
     * @brief mettre et enlever la pause
     */
    void pauseChanged();
    /**
     * @brief changer la vue
     * @param event
     */
    void viewChanged(QKeyEvent *event);
    /**
     * @brief déplacement d'un objet
     * @param event
     */
    void moveObject(QKeyEvent *event);
};

#endif // CONTROLER_H
