<p align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&height=180&color=gradient&text=Pavel%20Doltu%20cub3D%20Project%20%7C%2042%20Barcelona&fontAlign=50&fontAlignY=40&fontSize=40&desc=Raycasting%20Engine%20in%20C&descAlignY=60&descAlign=50" />
</p>

# 🎮 cub3D — Juego de Laberinto con Raycasting (Proyecto School 42)

**Idiomas:** [🇬🇧 English](README.en.md) | [🇷🇺 Русский](README.md)

## Descripción del Proyecto
**Cub3D** es un proyecto gráfico de School 42, cuyo objetivo es crear un juego "3D" al estilo del legendario **Wolfenstein 3D** (1992).  
![Status](https://img.shields.io/badge/status-finished-brightgreen.svg)

### Tecnologías:

- **Lenguaje:** C ![Language](https://img.shields.io/badge/language-C-blue.svg)
- **Biblioteca Gráfica:** [MLX42](https://github.com/codam-coding-college/MLX42) ![MiniLibX](https://img.shields.io/badge/MiniLibX-active-green.svg)
- **Compilador:** gcc
- **Estándar de Código:** Norminette (School 42) ![Norminette](https://img.shields.io/badge/style-Norminette-green.svg)
- **Plataforma:** Linux

### Objetivos del Proyecto:

-  Leer y validar archivo de configuración y mapa `.cub`
-  Implementar **ray casting** para renderizado pseudo-3D
-  Implementar control del jugador (WASD + rotación con flechas/ratón)
-  Aplicar texturas a las paredes según su orientación
-  Establecer diferentes colores para suelo y techo

---

## 📋 Tabla de Contenidos

- [Estructura del Proyecto](#estructura-del-proyecto)
- [¿Qué es Ray Casting?](#qué-es-ray-casting)
- [Fase 1: Parsing y Validación](#phase1)
- [Fase 2: Ray Casting y DDA](#phase2)
- [Fase 3: Renderizado](#phase3)
- [Instalación y Uso](#instalación-y-uso)

## Estructura del Proyecto

El proyecto está dividido condicionalmente en **3 fases principales**:

### 1️⃣ Lectura y Validación del Archivo `.cub`
- Parsing de configuración (texturas, colores)
- Parsing del mapa
- Validación: corrección de símbolos, presencia del jugador, cierre del mapa

### 2️⃣ Implementación de Algoritmos Ray Casting y DDA
- Inicialización de rayos para cada columna de pantalla
- DDA (Digital Differential Analyzer) para recorrer la cuadrícula
- Cálculo de distancia a paredes sin distorsión "ojo de pez"

### 3️⃣ Renderizado de Imagen
- Dibujo de suelo y techo
- Aplicación de texturas a paredes
- Correspondencia entre columna de pantalla y columna de textura
- Control del jugador y actualización de frames

---

## ¿Qué es Ray Casting?

**Ray Casting** es una técnica de renderizado de gráficos pseudo-3D (2.5D) que crea la ilusión de espacio tridimensional basándose en un mapa bidimensional.

### Idea Principal:
**Para cada columna vertical de pantalla:**
1. Lanzar un rayo desde la posición del jugador
2. El rayo viaja por el mapa hasta chocar con una pared
3. Medir la distancia a la pared
4. Dibujar una franja vertical: cuanto más cerca la pared, más alta la franja

**Resultado para resolución 640x480:** 640 franjas verticales de diferentes alturas que crean la ilusión de un laberinto 3D.

¡Esta técnica permitía ejecutar juegos en procesadores de principios de los años 90 — sin gráficos 3D reales, solo matemáticas inteligentes!

---
<a name="phase1"></a>
# Fase 1️⃣: Parsing y Validación

 - [Estructura del Archivo .cub](#--estructura-del-archivo-cub)
 - [Inicialización de Estructuras y Lectura de Archivo](#inicialización-de-estructuras-y-lectura-de-archivo)
 - [Parsing de Configuración](#parsing-de-configuración)
 - [Parsing del Mapa](#parsing-del-mapa)
 - [Validación del Mapa](#validación-del-mapa)
 - [BFS para Verificación de Cierre](#bfs-para-verificación-de-cierre)

## 📦 Estructura del Archivo `.cub`

El archivo .cub contiene toda la información necesaria para lanzar el juego:

- Rutas a texturas de cuatro paredes (`NO`, `SO`, `WE`, `EA`)  
- Colores de suelo y techo (`F`, `C`) en formato `R,G,B`  
- Mapa del laberinto con símbolos `0`, `1`, `N`, `S`, `E`, `W`  

Ejemplo de archivo de mapa:  
```text
NO ./textures/north_wall.png
SO ./textures/south_wall.png
WE ./textures/west_wall.png
EA ./textures/east_wall.png

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```
---

## Inicialización de Estructuras y Lectura de Archivo

- Inicialización del estado del juego *init_game()*, MLX e imagen *init_engine()*  
- En *init_game_data()* las estructuras se ponen a cero, se establecen valores predeterminados  
- El archivo *.cub* se lee línea por línea usando **get_next_line** (de libft)  
- Todas las líneas se guardan en un array dinámico

Verificaciones:  
✅ Número de argumentos en la llamada  
✅ Extensión del archivo — *.cub*  
✅ El archivo existe y es accesible para lectura  
✅ El archivo no está vacío  

---

## Parsing de Configuración

Encontrar el inicio del mapa *map_start*. Todo lo que está arriba es configuración, todo lo que está abajo es mapa. Parsear configuración:  
- Analizar líneas con identificadores `NO`, `SO`, `WE`, `EA`, `F`, `C`  
- Extraer rutas de texturas y valores RGB  
- Por ejemplo, línea: `NO ./textures/north_wall.png` se analiza en:  
	- identificador: `NO`  
	- ruta: `./textures/north_wall.png`  

Verificaciones:  
✅ Identificador correcto (NO/SO/WE/EA)  
✅ Ruta especificada y no vacía  
✅ Archivo de textura existe  
✅ Cada textura especificada exactamente una vez  

Parsing de colores:
Línea: `F 220,100,0`:  
identificador: `F` (floor/suelo)  
RGB: R=220, G=100, B=0  

Verificaciones:  
✅ Formato: R,G,B (sin espacios alrededor de comas)  
✅ Cada valor es un número de 0 a 255  
✅ Exactamente 3 componentes (R, G, B)  
✅ F y C especificados exactamente una vez  

**Conversión RGB a hex:**  
R=220, G=100, B=0  
hex = (R << 16) | (G << 8) | B  
hex = 0xDC6400  
MLX42 acepta color en formato RGBA (A - transparencia), no RGB como MiniLibX, así que antes de usar desplazamos el color 8 bits más (<< 8).

## Parsing del Mapa

- Leer todas las líneas del mapa en un array 2D *char map->grid*  
- Determinar ancho y alto del mapa  
- Símbolos válidos:  

`0` — espacio vacío (transitable)  
`1` — pared (intransitable)  
`N`, `S`, `E`, `W` — posición inicial y dirección de vista del jugador  
`(espacio)` — vacío más allá del mapa  

## Validación del Mapa

### Verificación de Cierre del Mapa

**¿Qué es un mapa "cerrado"?**  
Un mapa cerrado es aquel donde todas las celdas accesibles al jugador (símbolos `0`, `N/S/E/W`) están rodeadas de paredes (`1`). El jugador no debe poder "salir" más allá del área de juego. Si hay un agujero en el mapa (un espacio en el límite del área accesible), llevará a un comportamiento indefinido durante el renderizado.

**Criterio clave de no cierre:**  
***❌ El mapa no está cerrado si cualquier celda accesible (`0`) limita con un espacio (` `).***

En otras palabras:  
✅ Celda `0` puede limitar con `0` (otra celda accesible)  
✅ Celda `0` puede limitar con `1` (pared — límite del área de juego)  
❌ Celda `0` NO PUEDE limitar con ` ` (espacio — vacío más allá del mapa)  

**Sobre espacios en el mapa:**  
El espacio es un símbolo legal en el archivo `.cub`. Se usa para:
- Alineación del mapa (sangría izquierda)
- Marcar "nada" más allá del área de juego

Ejemplo de uso válido de espacios:
```
  111111111111    ← Espacios a la izquierda para sangría (OK)
  100000000001
111N0111100111
100001 10001      ← Espacio dentro rodeado de paredes (OK)
111111 11111
```

Pero si un espacio limita con una celda accesible — es un agujero:
```
11111111
1000000           ← Espacio a la derecha limita con `0` — ¡AGUJERO!
100N0001
10000001
11111111
```

---

### BFS para Verificación de Cierre

Para verificar el cierre del mapa se utiliza un algoritmo iterativo de búsqueda en anchura — **Breadth-First Search (BFS)**.

<p align="left">
  <img src="./images/DFSvsBFS.gif" alt="DFS vs BFS" width="300">
</p>

**¿Por qué BFS en lugar de Flood Fill recursivo (DFS)?**

| Criterio | BFS (iterativo) | DFS (recursivo) |
|----------|-----------------|-----------------|
| Seguridad | ✅ Sin riesgo de desbordamiento de pila | ❌ Puede fallar en mapas grandes |
| Complejidad | O(width × height) | O(width × height) |
| Memoria | Cola de tamaño width × height | Pila de llamadas (impredecible) |
| Legibilidad | ✅ Código iterativo fácil de depurar | Más difícil rastrear recursión |
| Completitud | ✅ Garantiza recorrer todas las celdas | ✅ Recorre todas las celdas |

---

### Estructuras de Datos para BFS

**Punto en el mapa:**
```c
typedef struct s_point
{
    int x;  // Coordenada X
    int y;  // Coordenada Y
} t_point;
```

**Cola circular:**
```c
typedef struct s_queue
{
    t_point *data;         // Array de puntos
    int     first;         // Índice del primer elemento
    int     last;          // Índice del último elemento
    int     current_size;  // Número actual de elementos
    int     capacity;      // Capacidad máxima
} t_queue;
```

**¿Por qué cola circular?**
- **Uso eficiente de memoria:** después de `dequeue` el espacio se libera y se reutiliza
- **O(1) para operaciones:** `enqueue` y `dequeue` se ejecutan en tiempo constante
- **Evitar desplazamientos:** no necesita desplazar constantemente elementos del array

**Datos para BFS:**
```c
typedef struct s_bfs_data
{
    int     **visited;  // Matriz de celdas visitadas (0 o 1)
    t_queue *queue;     // Cola para recorrido
} t_bfs_data;
```

---

### Cómo Funciona el Algoritmo

**Inicialización (`init_bfs`):**
1. Crear matriz `visited` de tamaño `[height][width]` (todos los valores = `0`)
2. Crear cola circular de tamaño `height × width`
3. Encontrar posición inicial del jugador (`N`, `S`, `E`, `W`)
4. Añadir posición inicial a la cola
5. Marcar celda inicial como visitada (`visited[y][x] = 1`)

**Recorrido en anchura (`process_bfs`):**

Mientras la cola no esté vacía:
1. Extraer celda de la cola (`dequeue`)
2. Verificar **4 celdas vecinas** (arriba, abajo, izquierda, derecha)
3. Para cada vecino llamar a `check_cell`:
   - Si es `0` (celda accesible):
     - Marcar como visitada
     - Añadir a la cola
   - Si es `1` (pared):
     - Ignorar (es el límite del área de juego)
   - Si es ` ` (espacio):
     - **¡ERROR!** Celda accesible limita con vacío
     - Mapa no cerrado → devolver `0`

**Resultado:**
- ✅ Todas las celdas accesibles verificadas sin encontrar espacios → mapa cerrado
- ❌ Al menos una celda accesible limita con espacio → mapa no cerrado

---

### Funciones Clave

| Función | Propósito |
|---------|-----------|
| `init_bfs` | Inicialización BFS: crea matriz `visited`, cola, añade posición inicial |
| `process_bfs` | Bucle principal de recorrido: extrae celda, verifica vecinos, devuelve resultado |
| `check_cell` | Verifica celda específica: `0` → añadir a cola, `1` → ignorar, ` ` → error |
| `can_visit` | Verifica si celda puede ser visitada: dentro de límites del mapa y no visitada antes |
| `enqueue` | Añade celda a la cola (considerando estructura circular) |
| `dequeue` | Extrae celda de la cola |

---

### Ejemplos de Validación

**✅ Mapa válido:**
```
        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```
- Todas las celdas accesibles (`0` y `N`) están rodeadas de paredes (`1`)
- Los espacios dentro del mapa están rodeados de paredes — no limitan con `0`

**❌ Mapa inválido (agujero a la derecha):**
```
11111111
10000000          ← Espacio a la derecha limita con `0`
100N0001
10000001
11111111
```
- BFS llegará al borde derecho y detectará espacio junto a `0`

---

### Archivos Clave (validación)

| Archivo | Propósito |
|---------|-----------|
| `validation.c` | Validación de símbolos del mapa y verificación de presencia del jugador |
| `bfs.c` | Implementación BFS para verificación de cierre del mapa |
| `queue.c` | Implementación de cola circular para BFS |
| `map_utils.c` | Funciones auxiliares para trabajar con el mapa |

<a name="phase2"></a>
# Fase 2️⃣: Ray Casting y DDA

## Contenidos de la Fase 2
- [Inicialización del Jugador y Cámara](#inicialización-del-jugador-y-cámara)
  - [Posición del Jugador](#posición-del-jugador)
  - [Vector de Dirección de Vista](#vector-de-dirección-de-vista-direction-vector)
  - [Plano de Cámara](#plano-de-cámara-camera-plane)
- [Bucle por Columnas de Pantalla](#bucle-por-columnas-de-pantalla)
  - [Cálculo de Dirección del Rayo](#cálculo-de-dirección-del-rayo)
- [Algoritmo DDA](#algoritmo-dda)
  - [Idea Principal](#idea-principal)
  - [Inicialización DDA](#inicialización-dda)
  - [Bucle DDA](#bucle-dda)
- [Cálculo de Distancia a la Pared](#cálculo-de-distancia-a-la-pared)
  - [Problema: Efecto Ojo de Pez](#problema-efecto-ojo-de-pez)
  - [Solución: Distancia Perpendicular](#solución-distancia-perpendicular)
- [Determinación del Lado de Colisión](#determinación-del-lado-de-colisión)
- [Estructuras de Datos para Ray Casting](#estructuras-de-datos-para-ray-casting)
- [Archivos Clave (fase 2)](#archivos-clave-fase-2)

---

Esta fase maneja las matemáticas del raycasting — el proceso de calcular distancias a las paredes y determinar qué debe ser visible en pantalla.

---
<p align="left">
  <img src="./images/raycasting.jpg" alt="Raycasting" width="300">
</p>
---

## Inicialización del Jugador y Cámara

Después del parsing exitoso del mapa, debe inicializarse la posición del jugador y configurar la "cámara". Esto ocurre en la función `init_player()`.

### Posición del Jugador

El jugador está ubicado en la celda donde se encontró el símbolo `N`, `S`, `E` o `W`:
- `player.pos_x` — coordenada X en la cuadrícula del mapa (ej., 5.5 — centro de celda)
- `player.pos_y` — coordenada Y en la cuadrícula del mapa

La posición del jugador se almacena en la estructura `t_player`:
```c
typedef struct s_player
{
    double  pos_x;      // Posición X
    double  pos_y;      // Posición Y
    double  dir_x;      // Dirección de vista X
    double  dir_y;      // Dirección de vista Y
    double  plane_x;    // Plano de cámara X
    double  plane_y;    // Plano de cámara Y
} t_player;
```

### Vector de Dirección de Vista (direction vector)

---
<p align="left">
  <img src="./images/raycasting2.png" alt="Raycasting" width="300">
</p>
---

Determina hacia dónde mira el jugador. Es un vector unitario:
- `dir_x` y `dir_y` forman el vector de dirección
- Depende del símbolo inicial en el mapa (`map.start_dir`):
  - `N` (North): `dir_x = 0`, `dir_y = -1` (mirando arriba)
  - `S` (South): `dir_x = 0`, `dir_y = 1` (mirando abajo)
  - `E` (East): `dir_x = 1`, `dir_y = 0` (mirando derecha)
  - `W` (West): `dir_x = -1`, `dir_y = 0` (mirando izquierda)

### Plano de Cámara (camera plane)

El plano de cámara es un vector perpendicular a la dirección de vista. Define el Campo de Visión (FOV):
- `plane_x` y `plane_y` — coordenadas del vector del plano de cámara
- La longitud de este vector determina el ángulo de visión
- Valor típico de longitud: `0.66` (aproximadamente 66° FOV)

**Ejemplo para jugador mirando al norte (N):**
```c
player.dir_x = 0.0;
player.dir_y = -1.0;
player.plane_x = 0.66;   // Perpendicular a la dirección
player.plane_y = 0.0;
```

**¿Por qué el plano es perpendicular?**  
El plano de cámara es la "pantalla" en el mundo del juego. Los rayos pasan por este plano, creando un cono de visión. Cuanto más largo el vector del plano, más ancho el FOV.

---

## Bucle por Columnas de Pantalla

El raycasting se realiza **para cada columna vertical de pantalla**. Si la resolución de pantalla es `800×600` (WIDTH × HEIGHT), entonces se necesitan lanzar 800 rayos.

Bucle principal en la función `render_frame()`:
```c
void render_frame(t_game *game)
{
    t_ray ray;
    int x;

    x = 0;
    while (x < WIDTH)
    {
        init_ray(game, x, &ray);     // Inicialización del rayo
        dda(game, &ray);              // Algoritmo DDA
        calculate_wall_distance(game, &ray);  // Cálculo de distancia
        draw_column(game, x, &ray);   // Renderizado de columna
        x++;
    }
}
```

### Cálculo de Dirección del Rayo

Para cada columna `x` (de 0 a WIDTH - 1) en la función `init_ray()`:

**1. Coordenada de cámara normalizada:**
```c
double camera_x = 2 * x / (double)WIDTH - 1;
```
- Valor de `-1` (borde izquierdo de pantalla) a `+1` (borde derecho)
- Cuando `x = 0`: `camera_x = -1`
- Cuando `x = WIDTH/2`: `camera_x = 0` (centro)
- Cuando `x = WIDTH-1`: `camera_x ≈ +1`

**2. Dirección del rayo:**
```c
ray->dir_x = game->player.dir_x + game->player.plane_x * camera_x;
ray->dir_y = game->player.dir_y + game->player.plane_y * camera_x;
```
- El rayo pasa por el plano de cámara
- El rayo central (`camera_x = 0`) coincide con la dirección de vista
- Los rayos laterales se desvían izquierda/derecha

**¿Por qué funciona esto?**
- Rayo central: `ray_dir = dir + plane * 0 = dir` (dirección de vista pura)
- Borde izquierdo: `ray_dir = dir + plane * (-1)` (desviación izquierda)
- Borde derecho: `ray_dir = dir + plane * (+1)` (desviación derecha)

**3. Celda actual del mapa:**
```c
ray->map_x = (int)game->player.pos_x;
ray->map_y = (int)game->player.pos_y;
```

---

## Algoritmo DDA

---
<p align="left">
  <img src="./images/dda.png" alt="DDA raycasting" width="300">
</p>
---

**DDA (Digital Differential Analyzer)** — un algoritmo que permite al rayo "avanzar" por la cuadrícula del mapa hasta la colisión con una pared.

### Idea Principal

El rayo se mueve por el mapa, cruzando límites de celdas. DDA determina:
- En qué celda está el rayo
- Qué límite de celda cruza a continuación (vertical u horizontal)
- Distancia a ese límite

### Inicialización DDA

La función `init_ray()` llama a funciones auxiliares de `ray_utils.c`:

**1. Cálculo de delta_dist (`calculate_delta_dist()`):**
```c
ray->delta_dist_x = fabs(1.0 / ray->dir_x);
ray->delta_dist_y = fabs(1.0 / ray->dir_y);
```
- `delta_dist_x` — distancia que el rayo recorre al desplazarse 1 celda en X
- `delta_dist_y` — lo mismo para Y

**2. Dirección de paso y distancia inicial (`init_step_and_side_dist()`):**

Si el rayo va en dirección X positiva (`ray->dir_x > 0`):
```c
ray->step_x = 1;
ray->side_dist_x = (ray->map_x + 1.0 - game->player.pos_x) * ray->delta_dist_x;
```

Si el rayo va en dirección X negativa (`ray->dir_x < 0`):
```c
ray->step_x = -1;
ray->side_dist_x = (game->player.pos_x - ray->map_x) * ray->delta_dist_x;
```

Lo mismo para Y.

- `step_x/step_y` — dirección de movimiento por la cuadrícula (+1 o -1)
- `side_dist_x/side_dist_y` — distancia al siguiente límite de celda

### Bucle DDA

La función `dda()` realiza el recorrido de la cuadrícula:

El rayo "avanza" por el mapa hasta chocar con una pared (`map->grid[ray->map_y][ray->map_x] == '1'`):

```c
void dda(t_game *game, t_ray *ray)
{
    int hit;

    hit = 0;
    while (hit == 0)
    {
        // Elegir qué límite cruzar a continuación
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;  // Moverse en X
            ray->map_x += ray->step_x;
            ray->side = 0;  // Límite vertical (West/East)
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;  // Moverse en Y
            ray->map_y += ray->step_y;
            ray->side = 1;  // Límite horizontal (North/South)
        }
        
        // Verificar colisión con pared
        if (game->map.grid[ray->map_y][ray->map_x] == '1')
            hit = 1;
    }
}
```

**Variable `ray->side`:**
- `side = 0` — el rayo golpeó pared vertical (West o East)
- `side = 1` — el rayo golpeó pared horizontal (North o South)

Esto es importante para:
- Elegir la textura correcta (NO/SO/WE/EA)
- Sombreado (las paredes verticales a menudo se hacen más oscuras para efecto de profundidad)

---

## Cálculo de Distancia a la Pared

Después de que el rayo choca con una pared, necesitamos calcular **distancia del jugador a la pared**.

### Problema: Efecto Ojo de Pez

Si usamos **distancia euclidiana** (línea recta del jugador al punto de colisión), obtendremos distorsión de "ojo de pez":
- Las paredes laterales parecerán más lejos
- La imagen estará curvada
- Las líneas paralelas parecerán distorsionadas

### Solución: Distancia Perpendicular

La función `calculate_wall_distance()` calcula **distancia perpendicular** — distancia a la pared a lo largo del plano de cámara.

**Fórmula:**

Si el rayo cruzó límite vertical (`ray->side == 0`):
```c
ray->perp_wall_dist = (ray->map_x - game->player.pos_x 
                       + (1 - ray->step_x) / 2) / ray->dir_x;
```

Si el rayo cruzó límite horizontal (`ray->side == 1`):
```c
ray->perp_wall_dist = (ray->map_y - game->player.pos_y 
                       + (1 - ray->step_y) / 2) / ray->dir_y;
```

**¿Por qué funciona esto?**
- `(1 - step_x) / 2` — corrección para dirección del rayo (0 o 1)
- Dividir por `ray->dir_x` (o `ray->dir_y`) para obtener proyección sobre la dirección de vista

**Resultado:** todas las paredes se muestran sin distorsión, las líneas paralelas permanecen paralelas.

---

## Determinación del Lado de Colisión

Necesitamos determinar desde qué lado el rayo golpeó la pared, para elegir la textura correcta de `t_textures`.

La función `select_texture()` en `draw_utils.c` determina la textura:

```c
mlx_texture_t *select_texture(t_game *game, t_ray *ray)
{
    if (ray->side == 0)  // Límite vertical
    {
        if (ray->dir_x > 0)
            return (game->textures.west);   // Rayo va derecha → pared oeste
        else
            return (game->textures.east);   // Rayo va izquierda → pared este
    }
    else  // Límite horizontal (ray->side == 1)
    {
        if (ray->dir_y > 0)
            return (game->textures.north);  // Rayo va abajo → pared norte
        else
            return (game->textures.south);  // Rayo va arriba → pared sur
    }
}
```

**Correspondencia de texturas:**
- **North (NO)** — `game->textures.north` — pared norte
- **South (SO)** — `game->textures.south` — pared sur  
- **West (WE)** — `game->textures.west` — pared oeste
- **East (EA)** — `game->textures.east` — pared este

---

## Estructuras de Datos para Ray Casting

Estructura principal del rayo `t_ray`:
```c
typedef struct s_ray
{
    double  dir_x;           // Dirección del rayo X
    double  dir_y;           // Dirección del rayo Y
    int     map_x;           // Celda actual del mapa X
    int     map_y;           // Celda actual del mapa Y
    double  delta_dist_x;    // Distancia entre límites verticales
    double  delta_dist_y;    // Distancia entre límites horizontales
    double  side_dist_x;     // Distancia al siguiente límite vertical
    double  side_dist_y;     // Distancia al siguiente límite horizontal
    int     step_x;          // Dirección de paso X (-1 o +1)
    int     step_y;          // Dirección de paso Y (-1 o +1)
    int     side;            // Tipo de límite (0 = vertical, 1 = horizontal)
    double  perp_wall_dist;  // Distancia perpendicular a la pared
} t_ray;
```

Estructura del jugador `t_player`:
```c
typedef struct s_player
{
    double  pos_x;      // Posición del jugador X
    double  pos_y;      // Posición del jugador Y
    double  dir_x;      // Dirección de vista X
    double  dir_y;      // Dirección de vista Y
    double  plane_x;    // Plano de cámara X (FOV)
    double  plane_y;    // Plano de cámara Y (FOV)
} t_player;
```

---

## Archivos Clave (fase 2)

| Archivo | Propósito |
|---------|-----------|
| `ray.c` | Funciones principales de raycasting: `init_ray()`, `dda()`, `calculate_wall_distance()` |
| `ray_utils.c` | Funciones auxiliares: `calculate_delta_dist()`, `init_step_and_side_dist()` |
| `render.c` | Bucle principal de renderizado `render_frame()` — recorre todas las columnas de pantalla |
| `player.c` | Inicialización del jugador `init_player()` — establece posición y dirección |
| `draw_utils.c` | Selección de textura `select_texture()` basada en lado de colisión |

<a name="phase3"></a>
# Fase 3️⃣: Renderizado

---
<p align="left">
  <img src="./images/rendering.png" alt="Rendering" width="300">
</p>
---

## Contenidos de la Fase 3
- [Cálculo de Altura de Pared en Pantalla](#cálculo-de-altura-de-pared-en-pantalla)
- [Definición de Límites de Dibujo](#definición-de-límites-de-dibujo)
- [Dibujo de Suelo y Techo](#dibujo-de-suelo-y-techo)
- [Trabajo con Texturas](#trabajo-con-texturas)
  - [Selección de Textura](#selección-de-textura)
  - [Cálculo de Coordenada X en Textura](#cálculo-de-coordenada-x-en-textura)
  - [Escalado Vertical de Textura](#escalado-vertical-de-textura)
- [Copiado de Píxeles a Pantalla](#copiado-de-píxeles-a-pantalla)
- [Estructuras de Datos para Renderizado](#estructuras-de-datos-para-renderizado)
- [Carga de Texturas](#carga-de-texturas)
- [Archivos Clave (fase 3)](#archivos-clave-fase-3)

---

Después de que el rayo encontró la pared y calculó la distancia a ella, necesitamos **dibujar una columna vertical** en la pantalla. Esta fase transforma datos matemáticos del ray-casting en una imagen visible.

---

## Cálculo de Altura de Pared en Pantalla

La altura de la pared en pantalla es **inversamente proporcional a la distancia**: cuanto más cerca la pared, más alta es.

**Fórmula:**
```c
int line_height = (int)(HEIGHT / ray->perp_wall_dist);
```

Donde:
- `HEIGHT` — altura de pantalla (600 píxeles)
- `ray->perp_wall_dist` — distancia perpendicular a la pared

**Ejemplo:**
- Si distancia = 1.0 → altura de pared = 600 píxeles (llena toda la pantalla)
- Si distancia = 2.0 → altura de pared = 300 píxeles (mitad de pantalla)
- Si distancia = 10.0 → altura de pared = 60 píxeles (muy lejos)

---

## Definición de Límites de Dibujo

La pared debe estar **centrada verticalmente** en la pantalla. Necesitamos calcular desde qué píxel empezar a dibujar y dónde terminar.

**Cálculo de punto inicial y final:**
```c
int draw_start = -line_height / 2 + HEIGHT / 2;
int draw_end = line_height / 2 + HEIGHT / 2;
```

**Problema:** la pared puede estar **muy cerca** y su altura puede exceder la altura de pantalla.

**Solución — recorte (clipping):**
```c
if (draw_start < 0)
    draw_start = 0;
if (draw_end >= HEIGHT)
    draw_end = HEIGHT - 1;
```

Estos valores se almacenan en la estructura `t_wall_draw`:
```c
typedef struct s_wall_draw
{
    mlx_texture_t   *current_texture;  // Textura seleccionada
    int             line_height;       // Altura de pared
    int             draw_start;        // Inicio de dibujo (Y)
    int             draw_end;          // Fin de dibujo (Y)
    int             tex_x;             // Coordenada X en textura
    int             clipped_top;       // Cuántos píxeles recortados arriba
} t_wall_draw;
```

**¿Por qué `clipped_top`?**  
Si la pared está muy cerca y `draw_start` fue < 0, necesitamos saber cuántos píxeles de textura fueron recortados desde arriba. Esto es importante para el mapeo correcto de textura.

```c
int clipped_top = 0;
if (draw_start < 0)
    clipped_top = -draw_start;
```

---

## Dibujo de Suelo y Techo

Antes de dibujar la pared, llenamos las partes superior e inferior de la columna con **color sólido**.

**Función `draw_column()` en `draw.c`:**

**1. Techo (de 0 a `draw_start`):**
```c
int y = 0;
while (y < draw_start)
{
    mlx_put_pixel(game->image, x, y, game->config.ceiling_color);
    y++;
}
```

**2. Suelo (de `draw_end` a `HEIGHT`):**
```c
y = draw_end;
while (y < HEIGHT)
{
    mlx_put_pixel(game->image, x, y, game->config.floor_color);
    y++;
}
```

Los colores `ceiling_color` y `floor_color` se establecen en el archivo de configuración `.cub` (líneas `C` y `F`) y se almacenan en `t_config` en formato `uint32_t` (RGBA).

---

## Trabajo con Texturas

### Selección de Textura

La función `select_texture()` en `draw_utils.c` determina qué textura usar según el lado de colisión:

```c
mlx_texture_t *select_texture(t_game *game, t_ray *ray)
{
    if (ray->side == 0)  // Límite vertical
    {
        if (ray->dir_x > 0)
            return (game->textures.west);
        else
            return (game->textures.east);
    }
    else  // Límite horizontal
    {
        if (ray->dir_y > 0)
            return (game->textures.north);
        else
            return (game->textures.south);
    }
}
```

### Cálculo de Coordenada X en Textura

Necesitamos determinar **qué columna vertical de textura** usar para la columna actual de pantalla.

**Función `calculate_tex_x()` en `draw_utils.c`:**

**1. Determinar punto de colisión con pared:**
```c
double wall_x;

if (ray->side == 0)  // Pared vertical
    wall_x = game->player.pos_y + ray->perp_wall_dist * ray->dir_y;
else  // Pared horizontal
    wall_x = game->player.pos_x + ray->perp_wall_dist * ray->dir_x;
```

`wall_x` — coordenada del punto de colisión en la pared (parte fraccionaria de 0.0 a 1.0).

**2. Mantener solo parte fraccionaria:**
```c
wall_x -= floor(wall_x);
```

Ahora `wall_x` está en rango [0.0, 1.0).

**3. Convertir a coordenada de textura:**
```c
int tex_x = (int)(wall_x * (double)texture->width);
```

**4. Inversión para algunos lados:**
```c
if ((ray->side == 0 && ray->dir_x > 0) || 
    (ray->side == 1 && ray->dir_y < 0))
    tex_x = texture->width - tex_x - 1;
```

Esto es necesario para que las texturas no estén reflejadas en paredes opuestas.

### Escalado Vertical de Textura

La textura tiene altura fija (ej., 64 o 128 píxeles), pero en pantalla la pared puede tener cualquier altura. Necesitamos **estirar o comprimir la textura**.

**Algoritmo en `draw_column()`:**

**1. Calcular paso de textura:**
```c
double step = (double)texture->height / (double)wall_draw.line_height;
```

**2. Calcular posición inicial en textura:**
```c
double tex_pos = wall_draw.clipped_top * step;
```

Si la pared fue recortada desde arriba (`clipped_top > 0`), empezamos no desde el inicio de la textura, sino desde la posición correspondiente.

**3. Para cada píxel de pared:**
```c
int y = wall_draw.draw_start;
while (y < wall_draw.draw_end)
{
    // Coordenada Y actual en textura
    int tex_y = (int)tex_pos;
    
    // Obtener color de píxel de textura
    uint32_t color = get_texture_color(texture, wall_draw.tex_x, tex_y);
    
    // Dibujar píxel en pantalla
    mlx_put_pixel(game->image, x, y, color);
    
    // Moverse por textura
    tex_pos += step;
    y++;
}
```

**¿Por qué usar `tex_pos` (double)?**  
La textura puede estar comprimida o estirada. `tex_pos` permite "deslizarse" suavemente por la textura, seleccionando los píxeles necesarios.

---

## Copiado de Píxeles a Pantalla

**Función `get_texture_color()` en `draw_utils.c`:**

Extrae color de píxel de textura MLX42:

```c
uint32_t get_texture_color(mlx_texture_t *texture, int tex_x, int tex_y)
{
    int index;
    uint32_t color;

    // Verificación de límites
    if (tex_x < 0 || tex_x >= (int)texture->width || 
        tex_y < 0 || tex_y >= (int)texture->height)
        return (0xFF000000);  // Color negro en error

    // Índice en array de píxeles
    index = (tex_y * texture->width + tex_x) * texture->bytes_per_pixel;

    // Extraer componentes RGBA
    color = (texture->pixels[index] << 24) |      // R
            (texture->pixels[index + 1] << 16) |  // G
            (texture->pixels[index + 2] << 8) |   // B
            texture->pixels[index + 3];           // A

    return (color);
}
```

**Formato MLX42:**
- Las texturas se almacenan en formato RGBA (4 bytes por píxel)
- `texture->pixels` — array de bytes
- `texture->bytes_per_pixel` — usualmente 4

**¿Por qué desplazamientos de bits?**  
MLX42 espera color en formato `0xRRGGBBAA`, así que necesitamos ensamblar 4 bytes en un número de 32 bits.

---

## Estructuras de Datos para Renderizado

**Estructura de dibujo de pared:**
```c
typedef struct s_wall_draw
{
    mlx_texture_t   *current_texture;  // Textura para esta pared
    int             line_height;       // Altura de pared en pantalla
    int             draw_start;        // Inicio de dibujo (coordenada Y)
    int             draw_end;          // Fin de dibujo (coordenada Y)
    int             tex_x;             // Coordenada X en textura
    int             clipped_top;       // Cuántos píxeles recortados arriba
} t_wall_draw;
```

**Estructura de texturas:**
```c
typedef struct s_textures
{
    mlx_texture_t   *north;  // Pared norte (NO)
    mlx_texture_t   *south;  // Pared sur (SO)
    mlx_texture_t   *west;   // Pared oeste (WE)
    mlx_texture_t   *east;   // Pared este (EA)
} t_textures;
```

**Configuración de colores:**
```c
typedef struct s_config
{
    char        *north;          // Ruta a textura NO
    char        *south;          // Ruta a textura SO
    char        *west;           // Ruta a textura WE
    char        *east;           // Ruta a textura EA
    uint32_t    floor_color;     // Color de suelo (RGBA)
    uint32_t    ceiling_color;   // Color de techo (RGBA)
} t_config;
```

---

## Carga de Texturas

Las texturas se cargan durante la inicialización del juego mediante la función `load_all_textures()` en `textures.c`.

**Función `load_texture()`:**
```c
int load_texture(mlx_texture_t **texture_field, const char *path)
{
    *texture_field = mlx_load_png(path);
    if (!(*texture_field))
    {
        error_msg("Failed to load texture");
        return (0);
    }
    return (1);
}
```

**Función `load_all_textures()`:**
```c
int load_all_textures(t_textures *textures, t_config *config)
{
    if (!load_texture(&textures->north, config->north))
        return (0);
    if (!load_texture(&textures->south, config->south))
        return (0);
    if (!load_texture(&textures->west, config->west))
        return (0);
    if (!load_texture(&textures->east, config->east))
        return (0);
    return (1);
}
```

**Importante:**
- MLX42 soporta solo formato PNG
- Las texturas deben existir y ser legibles
- Se recomienda usar texturas de tamaño potencia de dos (64×64, 128×128, 256×256)

---

## Archivos Clave (fase 3)

| Archivo | Propósito |
|---------|-----------|
| `draw.c` | Función principal `draw_column()` — dibuja columna vertical (techo, pared, suelo) |
| `draw_utils.c` | Utilidades de renderizado: `select_texture()`, `get_texture_color()`, `calculate_tex_x()` |
| `render.c` | Bucle principal de renderizado `render_frame()` — recorre todas las columnas de pantalla |
| `textures.c` | Carga de texturas: `load_texture()`, `load_all_textures()` |
| `main.c` | Bucle del juego `game_loop()` — llama a `render_frame()` cada frame |

# Instalación y Uso

## Contenidos
- [Requisitos](#requisitos)
- [Compilación](#compilación)
- [Ejecución](#ejecución)
- [Controles](#controles)
- [Ejemplos de Mapas](#ejemplos-de-mapas)
- [Solución de Problemas](#solución-de-problemas)

---

## Requisitos

### Sistema Operativo
- **Linux** (proyecto desarrollado y probado en Linux)
- Puede funcionar en macOS (requiere adaptación de MLX42)

### Dependencias
- **gcc** — compilador C
- **make** — sistema de construcción
- **MLX42** — biblioteca gráfica ([GitHub](https://github.com/codam-coding-college/MLX42))
- **GLFW** — biblioteca para trabajar con ventanas y OpenGL (requerida para MLX42)
- **libft** — biblioteca personalizada de funciones C (debe estar en el proyecto)

### Instalación de Dependencias (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install build-essential libglfw3-dev libglfw3
```

### Instalación de Dependencias (macOS)
```bash
brew install glfw
```

---

## Compilación

### Versión obligatoria (mandatory)
```bash
make
```

Este comando:
- Compila la biblioteca `libft`
- Compila MLX42 (si aún no está compilada)
- Construye el ejecutable `cub3D`

### Versión bonus
```bash
make bonus
```

La versión bonus incluye características adicionales:
- Minimapa
- Control con ratón
- Elementos adicionales de interfaz

### Limpieza
```bash
make clean    # Elimina archivos objeto
make fclean   # Elimina archivos objeto y ejecutable
make re       # Reconstrucción completa (fclean + make)
```

---

## Ejecución

### Ejecución básica
```bash
./cub3D maps/map.cub
```

### Formato de comando
```bash
./cub3D <ruta_al_archivo.cub>
```

**Argumentos:**
- `<ruta_al_archivo.cub>` — ruta al archivo de configuración del mapa

**Verificaciones al iniciar:**
- ✅ Debe pasarse exactamente 1 argumento (ruta al mapa)
- ✅ El archivo debe tener extensión `.cub`
- ✅ El archivo debe existir y ser legible
- ✅ El archivo no debe estar vacío

### Ejemplos de ejecución
```bash
# Ejecutar con mapa predeterminado
./cub3D maps/default.cub

# Ejecutar con mapa personalizado
./cub3D maps/my_custom_map.cub

# Ejecutar con ruta absoluta
./cub3D /home/user/maps/test.cub
```

---

## Controles

### Mandatory (parte obligatoria)

**Movimiento:**
- `W` — moverse hacia adelante
- `S` — moverse hacia atrás
- `A` — moverse a la izquierda (strafing)
- `D` — moverse a la derecha (strafing)

**Rotación de cámara:**
- `←` (flecha izquierda) — rotar cámara izquierda
- `→` (flecha derecha) — rotar cámara derecha

**Salir:**
- `ESC` — salir del juego
- `X` (botón cerrar ventana) — salir del juego

### Bonus (parte bonus)

**Además de mandatory:**
- **Ratón** — movimiento del ratón rota la cámara
  - Sensibilidad del ratón: `0.002` (puede configurarse en `cube.h`)

**Minimapa:**
- Se muestra en esquina de pantalla
- Muestra posición del jugador (punto rojo)
- Muestra paredes (color gris)
- Radio de visibilidad: 8 celdas

---

## Ejemplos de Mapas

El proyecto debe incluir mapas de prueba en carpeta `maps/`:

### Mapa simple
```bash
./cub3D maps/simple.cub
```
- Laberinto pequeño para primera ejecución
- Verificación de funcionalidad básica

### Mapa complejo
```bash
./cub3D maps/complex.cub
```
- Laberinto grande con muchos giros
- Prueba de rendimiento

### Mapa con espacios
```bash
./cub3D maps/spaces.cub
```
- Mapa con espacios dentro y en bordes
- Verificación de parsing y validación

### Mapa mínimo
```bash
./cub3D maps/minimal.cub
```
- Mapa válido mínimo posible
- 3×3 celdas con jugador en centro

---

## Solución de Problemas

### Error: "Error: Invalid file extension"
**Causa:** El archivo no tiene extensión `.cub`  
**Solución:** Use archivo con extensión correcta: `map.cub`

### Error: "Error: Failed to open file"
**Causa:** El archivo no existe o no hay permisos de lectura  
**Solución:** 
- Verifique la ruta al archivo
- Verifique permisos de acceso: `chmod 644 map.cub`

### Error: "Error: Invalid map"
**Causa:** El mapa no es válido (no cerrado, símbolos incorrectos, etc.)  
**Solución:**
- Verifique que el mapa esté rodeado de paredes (`1`)
- Verifique que haya exactamente un jugador (`N`, `S`, `E`, `W`)
- Verifique que no haya símbolos inválidos

### Error: "Error: Failed to load texture"
**Causa:** Textura no encontrada o corrupta  
**Solución:**
- Verifique rutas a texturas en archivo `.cub`
- Asegúrese de que las texturas estén en formato PNG
- Verifique permisos de acceso a archivos de texturas

### Error: "Error: Invalid color format"
**Causa:** Formato de color incorrecto en archivo `.cub`  
**Solución:**
- Formato: `F 220,100,0` (R,G,B sin espacios)
- Valores de 0 a 255
- Exactamente 3 componentes

### Error: MLX no se inicializa
**Causa:** Problemas con sistema gráfico o GLFW  
**Solución:**
```bash
# Ubuntu/Debian
sudo apt-get install libglfw3-dev libglfw3

# Verifique que X11 esté ejecutándose (para Linux)
echo $DISPLAY

# Si está vacío, intente:
export DISPLAY=:0
```

### Bajo rendimiento (FPS)
**Causa:** Texturas pesadas o resolución grande  
**Solución:**
- Reduzca resolución en `cube.h`: `#define WIDTH 640` y `#define HEIGHT 480`
- Use texturas más pequeñas (64×64 en lugar de 256×256)
- Verifique optimización de compilación: flag `-O2` en Makefile

### El juego no responde a entrada
**Causa:** Ventana sin foco o problema de manejo de eventos  
**Solución:**
- Haga clic en la ventana del juego
- Asegúrese de que `key_handler` esté registrado en MLX
- Verifique que se use `mlx_key_hook()`

### Fallo de Segmentación (Segmentation Fault)
**Causa:** Acceso a memoria no inicializada o límites de array excedidos  
**Solución:**
- Ejecute con valgrind: `valgrind ./cub3D maps/map.cub`
- Verifique inicialización de todas las estructuras
- Verifique límites de arrays en parsing del mapa

---

## Comandos Adicionales

### Verificación de fugas de memoria
```bash
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/map.cub
```

### Ejecutar con información de depuración
```bash
# Compilar con flags de debug
make CFLAGS="-g -fsanitize=address"

# Ejecutar
./cub3D maps/map.cub
```

### Verificación Norminette (School 42)
```bash
norminette *.c *.h libft/
```
