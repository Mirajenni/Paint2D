#ifndef PAINTTELA_H
#define PAINTTELA_H

#include <QWidget>
#include <QtOpenGL>
#include <GL/glu.h>
#include <QGLWidget>
#define NUM 15

class PaintTela : public QGLWidget
{
    Q_OBJECT
public:
    explicit PaintTela(QWidget *parent = 0);
public slots:
    void alterarLados(int l);
    void alterarRaio(double r);
    void criarFigura();
    void alterarR(int verm);
    void alterarG(int verde);
    void alterarB(int azul);
    void selecionar(int poligono);
    void transladarX(double x);
    void transladarY(double y);
    void escalarX(double x);
    void escalarY(double y);
    void rotacionar(double a);
    void cisalharX(double x);
    void cisalharY(double y);
    void excluirFigura ();
    void excluirTodos ();
    void tamanhoMalha(int t);
    void exibirMalha();
protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
private:
    int p; //polígono
    boolean poligonos[NUM]= {FALSE};
    boolean malha;
    int lados[NUM];
    double raio[NUM];
    double eixoX[NUM], eixoY[NUM];
    double escalaX[NUM], escalaY[NUM];
    double angulo[NUM];
    double cisalhaX[NUM], cisalhaY[NUM];
    int red[NUM], green[NUM], blue[NUM];
    int tam;

};

#endif // PAINTTELA_H
