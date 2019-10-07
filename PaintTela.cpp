#include "PaintTela.h"
#include <cmath>
#include <stdlib.h>
#include <time.h>

PaintTela::PaintTela(QWidget *parent) : QGLWidget(parent)
{
    malha = 0;
    tam = 30;
    p = 0;
}

void PaintTela::initializeGL() {
    glShadeModel(GL_SMOOTH);

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void PaintTela::selecionar(int poligono) {
    if (p!=poligono && poligono>= 0 && poligono<15) {
        p = poligono;
    }
    updateGL();
}

void PaintTela::alterarLados(int l) //não buga, faz de boa
{
    if (l != lados[p] && lados[p] >= 3 && lados[p] <= 60)
        lados[p] = l;
    updateGL();
}

void PaintTela::alterarRaio(double r) //ele vai e volta
{
    if (r != raio[p] && r >= 1.0 && r <= 10.0)
        raio[p] = r;
    updateGL();
}

void PaintTela::criarFigura() {
    srand(time(NULL));
    if(poligonos[p]==FALSE) {//não criado ainda
        lados[p] = 3;
        raio[p] = 1.0;
        red[p] = (rand()%256);
        green[p] = (rand()%256);
        blue[p] = (rand()%256);
        eixoX[p] = 0.0;
        eixoY[p] = 1.0;
        escalaX[p] = 1.0;
        escalaY[p] = 1.0;
        angulo[p] = 0.0;
        cisalhaX[p] = 0.0;
        cisalhaY[p] = 0.0;
        poligonos[p]= 1; //ativa
    }
    updateGL();
}

void PaintTela::alterarR(int verm) {
    if (red[p] != verm && verm >= 0 && verm <= 255) {
        red[p] = verm;
    }
    updateGL();
}

void PaintTela::alterarG(int verde) {
    if (green[p] != verde && verde >= 0 && verde <= 255) {
        green[p] = verde;
    }
    updateGL();
}

void PaintTela::alterarB(int azul) {
    if (blue[p] != azul && azul >= 0 && azul <= 255) {
        blue[p] = azul;
    }
    updateGL();
}

void PaintTela::transladarX(double x) {
    if(x!=eixoX[p] && eixoX[p] >= -20.0 && eixoX[p] <=20.0)
        eixoX[p] = x;
    updateGL();
}

void PaintTela::transladarY(double y) {
    eixoY[p] = y;
    updateGL();
}

void PaintTela::escalarX(double x) {
    if (x!= escalaX[p] && escalaX[p]>= 1.0 && escalaX[p] <= 10.0)
        escalaX[p] = x;
    updateGL();
}

void PaintTela::escalarY(double y){
    if (y!= escalaY[p] && escalaY[p]>= 1.0 && escalaY[p]<= 10.0)
        escalaY[p] = y;
    updateGL();
}

void PaintTela::rotacionar(double a) {
    if (a!= angulo[p] && angulo[p] >= -360.0 && angulo[p] <= 360.0)
        angulo[p] = a;
    updateGL();
}

void PaintTela::cisalharX(double x) {
    if (x!= cisalhaX[p] && cisalhaX[p]>= 0.0 && cisalhaX[p]<= 3.0)
        cisalhaX[p] = x;
    updateGL();
}

void PaintTela::cisalharY(double y) {
    if (y!= cisalhaY[p] && cisalhaY[p]>= 0.0 && cisalhaY[p]<= 3.0)
        cisalhaY[p] = y;
    updateGL();
}

void PaintTela::excluirFigura () {
    if (poligonos[p] == TRUE) { //se o polígono existir, desativar
        poligonos[p] = FALSE;
    }
    updateGL();
}

void PaintTela::excluirTodos () {
    for(int i=0; i<15; i++) {
        if (poligonos[i] == TRUE) { //se o polígono existir, desativa ele
            poligonos[i] = FALSE;
        }
    }
    updateGL();
}
void PaintTela::tamanhoMalha(int t) {
    tam = t;
    updateGL();
}

void PaintTela::exibirMalha() {
    if (malha == FALSE) {
        malha = TRUE;
    }
    else {
        malha = FALSE;
    }
    updateGL();
}


void PaintTela::resizeGL(int width, int height)
{
    double menorX = 0, maiorX = 10, menorY = 0, maiorY = 10;
    glViewport(0, 0, (GLint)width, (GLint)height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width > height)
    {
        height = height?height:1;
        double novaLargura = (maiorX - menorX) * width / height;
        double difLargura = novaLargura - (maiorX - menorX);
        menorX = 0.0 - difLargura / 2.0;
        maiorX = 10 + difLargura / 2.0;
    }
    else
    {
        width = width?width:1;
        double novaAltura = (maiorY - menorY) * height / width;
        double difAltura = novaAltura - (maiorY - menorY);
        menorY = 0.0 - difAltura / 2.0;
        maiorY = 10 + difAltura / 2.0;
    }
    gluOrtho2D(menorX, maiorX, menorY, maiorY);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void PaintTela::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); // limpa todas as transformações

    for (int j=0; j<NUM; j++) {
        if(poligonos[j]==TRUE) { //se ele EXISTE
            glLoadIdentity(); //limpa, se não uma figura leva a outra junto
            glTranslated(eixoX[j], eixoY[j], 0.0);
            glRotated(angulo[j], 0.0, 0.0, 1.0);
            glScaled(escalaX[j], escalaY[j], 0.0);
            GLdouble m[16] = {
                1.0, cisalhaY[j], 0.0, 0.0,
                cisalhaX[j], 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                0.0, 0.0, 0.0, 1.0};
            glMultMatrixd(m);

            glLineWidth(1);
            glColor3ub(red[j], green[j], blue[j]);
            glBegin(GL_POLYGON);
            for (int i = 0; i < lados[j]; ++i)
                  glVertex2f(raio[j]*cos(i*2*3.14159265/lados[j]), raio[j]*sin(i*2*3.14159265/lados[j]));
            glEnd();

            glLineWidth(2);
            glColor3ub(red[j], green[j], blue[j]);
            glBegin(GL_LINE_LOOP);
            for (int i = 0; i < lados[j]; ++i)
                glVertex2f(raio[j]*cos(i*2*3.14159265/lados[j]), raio[j]*sin(i*2*3.14159265/lados[j]));
            glEnd();
        }
    }

    if (malha==TRUE) { //Se ativar a malha, desenhar as grades
        glLoadIdentity();
        float i=-8.43;
        float incremento = (26.84/float(tam)); //O range do tamanho divido pela quantidade desejada
        do {
            glLineWidth(1);
            glColor3f(0,0,0);
            glBegin(GL_LINES);
                glVertex2f(i,20);
                glVertex2f(i,-10);
            glEnd();
            glColor3f(0,0,0);
            glBegin(GL_LINES);
                glVertex2f(20,i);
                glVertex2f(-10,i);
            glEnd();
            i=i+incremento;
        }while(i<=18.41);
    }
}


