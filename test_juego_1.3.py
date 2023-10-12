# Importamos las librerías necesarias
import pygame
import random

# Definimos los colores que utilizaremos
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)

# Definimos las dimensiones de la ventana
WIDTH = 800
HEIGHT = 600

# Inicializamos Pygame
pygame.init()

# Creamos la ventana
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Juego de la Oca")

# Creamos una clase para representar las casillas del tablero
class Casilla:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def dibujar(self):
        pygame.draw.rect(screen, WHITE, [self.x, self.y, 50, 50], 2)

# Creamos una lista con todas las casillas del tablero
casillas = []
for i in range(10):
    for j in range(10):
        casillas.append(Casilla(i * 50 + 100, j * 50 + 100))

# Creamos una función para dibujar el tablero
def dibujar_tablero():
    screen.fill(BLACK)
    for casilla in casillas:
        casilla.dibujar()
    pygame.display.update()

# Creamos una función para mover el jugador por el tablero
def mover_jugador(posicion_actual):
    # Generamos un número aleatorio entre 1 y 6 para simular el lanzamiento de un dado
    dado = random.randint(1, 6)
    # Movemos al jugador a la nueva posición
    nueva_posicion = posicion_actual + dado
    # Si el jugador llega al final del tablero, lo hacemos retroceder hasta la casilla anterior al final
    if nueva_posicion > len(casillas) - 1:
        nueva_posicion = len(casillas) - (nueva_posicion - len(casillas)) - 2
    return nueva_posicion

# Creamos una función para dibujar al jugador en su posición actual
def dibujar_jugador(posicion_actual):
    pygame.draw.circle(screen, RED, [casillas[posicion_actual].x + 25, casillas[posicion_actual].y + 25], 20)

# Definimos la posición inicial del jugador y dibujamos el tablero y al jugador por primera vez
posicion_actual = 0
dibujar_tablero()
dibujar_jugador(posicion_actual)

# Bucle principal del juego
while True:
    # Esperamos a que el usuario cierre la ventana o presione alguna tecla para lanzar el dado
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            quit()
        if event.type == pygame.KEYDOWN:
            posicion_actual = mover_jugador(posicion_actual)
            dibujar_tablero()
            dibujar_jugador(posicion_actual)

    # Actualizamos la pantalla y esperamos un poco antes de volver a actualizarla
    pygame.display.update()
    pygame.time.wait(100)
