#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TIMESTEPS 1000  // Número de pasos de tiempo
#define G 9.81  // Constante gravitacional
#define DT 0.01  // Paso de tiempo

typedef struct {
    double x, y;
    double vx, vy;
    double fx, fy;
    double mass;
} Particle;

void initializeParticles(Particle* particles, int N) {
    for (int i = 0; i < N; i++) {
        particles[i].x = (double)rand() / RAND_MAX * 100.0;
        particles[i].y = (double)rand() / RAND_MAX * 100.0;
        particles[i].vx = 0.0;
        particles[i].vy = 0.0;
        particles[i].mass = 1.0 + (double)rand() / RAND_MAX;
    }
}

void computeForces(Particle* particles, int N) {
    // Reiniciamos las fuerzas
    for (int i = 0; i < N; i++) {
        particles[i].fx = 0.0;
        particles[i].fy = -particles[i].mass * G;  // Solo gravedad
    }
}

void updateVelocities(Particle* particles, int N) {
    for (int i = 0; i < N; i++) {
        particles[i].vx += particles[i].fx / particles[i].mass * DT;
        particles[i].vy += particles[i].fy / particles[i].mass * DT;
    }
}

void updatePositions(Particle* particles, int N) {
    for (int i = 0; i < N; i++) {
        particles[i].x += particles[i].vx * DT;
        particles[i].y += particles[i].vy * DT;
    }
}

int main() {
    int N = 10000000;  // Ahora puedes definir un tamaño más grande

    // Asignamos memoria dinámica para las partículas
    Particle* particles = (Particle*)malloc(N * sizeof(Particle));
    if (particles == NULL) {
        printf("Error al asignar memoria\n");
        return 1;
    }

    initializeParticles(particles, N);

    clock_t begin = clock();

    for (int t = 0; t < TIMESTEPS; t++) {
        computeForces(particles, N);  // Cálculo de fuerzas
        updateVelocities(particles, N);  // Actualización de velocidades
        updatePositions(particles, N);  // Actualización de posiciones
    }

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecución: %f segundos\n", time_spent);

    // Liberamos la memoria dinámica asignada
    free(particles);

    return 0;
}
