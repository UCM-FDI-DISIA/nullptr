# **Timeless Deck : ¡Es Tiempo! GDD - un juego creado por Nullptr**

---

**Integrantes:**

DANIEL ALONSO HERRANZ

LUIS RAFAEL ARGANDOÑA BLACIDO

MIGUEL CURROS GARCÍA

PABLO GONZÁLEZ ARROYO

ALEJANDRO GONZÁLEZ SÁNCHEZ

DIEGO LÓPEZ BALBOA

JAVIER MURILLO GONZÁLEZ

JOSE EDUARDO ROBLES ROCA

RAFAEL VILCHES HERNÁNDEZ

YI WANG QIU

---

## **Ficha Técnica**

<table>
  <tr>
   <td><strong>Título</strong>
   </td>
   <td>Timeless Deck
   </td>
  </tr>
  <tr>
   <td><strong>PEGI</strong>
   </td>
   <td>12 (non-realistic or non-detailed violence in a fantasy environment)
   </td>
  </tr>
  <tr>
   <td><strong>Género</strong>
   </td>
   <td>Arcade, acción, roguelike, deck builder
   </td>
  </tr>
  <tr>
   <td><strong>Público objetivo</strong>
   </td>
   <td>Jóvenes y adolescentes entre 15 y 25 años
   </td>
  </tr>
  <tr>
   <td><strong>Plataforma</strong>
   </td>
   <td>PC (Windows)
   </td>
  </tr>
  <tr>
   <td><strong>Modos de juego</strong>
   </td>
   <td>Un jugador
   </td>
  </tr>
  <tr>
   <td><strong>Controles</strong>
   </td>
   <td>Teclado + Ratón / Gamepad
   </td>
  </tr>
</table>

## **Descripción**

_Timeless Deck_ es un juego arcade en el cual el jugador deberá superar distintos niveles combatiendo enemigos. Dispondrás de cartas que te servirán de armas; así que, ¡es tiempo de hacerte con todas! 


## **Mecánicas**

**1. Personaje**

El jugador controlará al personaje quien constará de las siguientes mecánicas:
* <span style="text-decoration:underline;">Movimiento:</span> se podrá mover en dos dimensiones (top-down) hacia cualquier dirección.
* <span style="text-decoration:underline;">Apuntado:</span> se podrá usar la carta en la dirección deseada apuntando con el ratón o joystick.
* <span style="text-decoration:underline;">Sistema de vida:</span> se contará con unos puntos de vida (detallados más adelante).
* <span style="text-decoration:underline;">Sistema de maná:</span> se contará con una cantidad de maná que podrá incrementar durante el juego y se podrá usar para realizar las habilidades de las cartas (detallado más adelante).

**2. Recursos**
1. **Maná**

Permite al jugador usar las habilidades especiales de las cartas. El jugador empezará con una cantidad concreta de maná y solo podrá tener hasta un máximo, el cual puede ser modificado por un objeto (detallada en sus estadísticas más adelante).

Este recurso se obtendrá al matar enemigos (detallado en la sección de enemigos). Los enemigos lo soltarán y lo dejarán en el suelo, teniendo el jugador que recogerlo pasando cerca del mismo, a excepción de si se acaba la oleada, que entonces todo el maná del suelo pasará al jugador automáticamente.

2. **Tiempo**

El tiempo será la moneda del juego que se usará en la tienda para comprar cartas que no tuviera ya el jugador.

Este recurso se obtendrá al completar un nivel, tras hacer un cómputo de los enemigos eliminados, el tiempo transcurrido y el daño recibido en ese nivel.

3. **Éter espacio-temporal**

El éter espacio-temporal será el principal recurso que permitirá al jugador pasar de nivel. El jugador siempre empezará con 0 éter y deberá conseguir la cantidad determinada por cada nivel.

Además, se le proporcionará al jugador automáticamente una vez elimine al enemigo, viéndose reflejado en la carga de la máquina en el HUD (detallado más adelante).

**3. Cartas**

Las cartas son armas que el jugador deberá usar para derrotar a los enemigos. Estas tendrán munición. Cuando se agote la munición, la carta pasará a una pila de descartes. Serán a la vez consumibles que proporcionarán una habilidad especial al jugador.

Por tanto, las cartas consistirán de un ataque y una habilidad: 
* <span style="text-decoration:underline;">Ataque:</span> puede ser un ataque a distancia (ej: pistola) o un ataque a melee (ej: espada), el cual causará un daño determinado a los enemigos. Además, puede infligir un efecto sobre los enemigos que hayan sido atacados pero no derrotados. Cada uso gasta una unidad de munición.
* <span style="text-decoration:underline;">Habilidad:</span> puede consistir en un boost temporal de una estadística del jugador o un ataque especial más potente que uno normal. Para usar la habilidad, se debe consumir la carta usando una cantidad de maná determinada y descartándola inmediatamente de la mano. La potencia de la habilidad dependerá de la cantidad de munición restante al consumir la carta: a mayor munición, mayor potencia.

Cada carta estará relacionada con una época: pasado, presente o futuro. Esto influirá en cómo el jugador podrá obtenerlas durante el juego.


**4. Sistema de flujo de cartas**

El jugador comienza con un mazo de 4 cartas predefinido. Como máximo, se podrá tener 15 cartas diferentes en su mazo de combate y nunca podrá llevar menos de 4. Este se podrá modificar en el inventario, antes de seleccionar algún nodo del mapa. 

Al comienzo de un combate, se robarán 4 cartas aleatorias del mazo y estas pasarán a formar parte de la mano, las cuales se usarán para el combate. Se van usando las cartas y, una vez consumidos todos los usos de una carta, esta es descartada y va a la pila de descartes. Cuando el jugador se queda sin cartas en la mano, roba 4 cartas del mazo. Si se intenta robar de un mazo vacío, la pila de descartes se baraja, se vuelve a colocar en el lugar del mazo y el jugador roba de este. 

![cardsLoop](https://github.com/UCM-FDI-DISIA/nullptr/blob/main/docs/images/gameLoop.png)

**5. Objetos pasivos (Reliquias)**

Los objetos pasivos proporcionarán un aumento permanente a las estadísticas del jugador para el resto de la partida. Siempre será menor que un aumento temporal proporcionado por una habilidad de una carta.

Estos se podrán obtener de manera aleatoria en los cofres del mundo. Durante una partida no aparecerá dos veces el mismo objeto.

**6. Enemigos**

Los enemigos son el principal peligro al que se enfrentará el jugador. Acabar con ellos será esencial para poder cargar la máquina (terminar el nivel) y usar habilidades. 

Habrá 3 tipos de enemigos: los TANQUES (T), los LUCHADORES (L) y los TIRADORES (T). Estos serán los mismos para el resto del juego, pero irán variando en aspecto y fuerza según lo avanzado del nivel y la época en la que se encuentre el jugador. Compartirán las siguientes mecánicas:
* <span style="text-decoration:underline;">Movimiento:</span> top-down con patrones de movimiento diferentes por enemigo.
* <span style="text-decoration:underline;">Ataque:</span> cuerpo a cuerpo o a distancia con diferentes patrones según el enemigo.
* <span style="text-decoration:underline;">Muerte:</span> los enemigos al morir, dependiendo de qué tipo sean, soltarán cierta cantidad de maná al suelo que podrá ser recogida por el jugador. Además, al morir, estos proporcionarán éter espacio-temporal que contribuirá a la carga de la máquina del tiempo, permitiendo al jugador completar el nivel.

Sus comportamientos serán distintos para cada tipo:
* <span style="text-decoration:underline;">Tanque:</span> avanza hacia el jugador, pudiendo atacar cuerpo a cuerpo o en un área corta.
* <span style="text-decoration:underline;">Luchador:</span> avanza hacia el jugador con la intención de colisionar con él, atacando cuerpo a cuerpo.
* <span style="text-decoration:underline;">Tirador:</span> avanza hacia el jugador pero mantiene las distancias de forma que pueda atacar al jugador con proyectiles a distancia.

Las estadísticas y características de los enemigos se explican más adelante.

**7. Mundo y nodos**

La navegación entre las diferentes fases de juego se llevará a cabo a través de un mapa de nodos. Este se generará con nodos interconectados aleatoriamente al comienzo de cada partida, pero siempre cumplirá ciertos parámetros.

La navegación de este mapa será en un único sentido, por lo que no se podrá retroceder en ningún momento. Las distintas ramas llevarán al mismo nodo final: la batalla contra el jefe final **_El Guardián del Tiempo_**. 

Los tipos de nodos (fases de juego) son:
* <span style="text-decoration:underline;">Nodos de combate:</span> cada uno está ubicado en un momento temporal diferente: pasado, presente o futuro. Esto condiciona los tipos de enemigos que aparecerán y las recompensas que el jugador obtendrá. El jugador deberá vencer enemigos para ir llenando el medidor de la máquina del tiempo. Cuando se llene, se dará la posibilidad de abrir un portal para salir del nivel. El jugador no tiene porqué entrar en este directamente, pero la dificultad del nivel se elevará de forma exponencial si decide seguir en el nivel. Al completar el nivel, el jugador volverá al mapa de nodos para elegir su próximo destino.
* <span style="text-decoration:underline;">Nodos de tienda:</span> se le ofrecerán al jugador 4 cartas que no tenga ya en su inventario. Se garantiza al menos una carta de futuro, una de presente y una de pasado. La cuarta carta será aleatoria. Cada carta tendrá un precio asociado. El jugador podrá, si se lo puede permitir, comprar hasta las 4 cartas ofertadas en cada tienda.
* <span style="text-decoration:underline;">Nodos de cofre:</span> el jugador abrirá un cofre en el que encontrará un objeto que le otorgará beneficios pasivos de forma aleatoria.
* <span style="text-decoration:underline;">Nodo del **_Guardián del Tiempo_**:</span> Batalla contra el jefe final. Si se le consigue derrotar se obtendrá el final del juego.  

## **Dinámicas**

**1. Bucle de juego**

El bucle de juego consistirá en ir superando niveles donde se debe matar enemigos usando cartas para completarlos, de forma que al terminar se consiga una cantidad de oro como recompensa, la cual servirá para comprar más cartas en tiendas. También se debe completar niveles para tener la posibilidad de acceder a cofres, los cuales darán objetos pasivos que aumentarán las estadísticas permanentemente. Tiene dos profundidades:

1. **Mapa del mundo:**

Desde donde empieza el juego y a donde se volverá siempre tras finalizar cada nodo. Aquí, se puede elegir a qué nodo desplazarse de los que tiene disponibles y acceder a su inventario donde se puede preparar el mazo para el combate.

2. **Combate**

En esta fase, el jugador tomará control del personaje principal dentro de una gran sala rectangular y plana. Se intentará derrotar a un cierto número de enemigos para reparar la máquina del tiempo y así tener la opción de salir del combate.

**2. Sistema de economía** {#2-sistema-de-economía}

Durante el juego, al derrotar enemigos, ganarás monedas de oro que sirven para gastar en la tienda.

Este oro se otorgará al final del combate y se entregará en una cantidad dependiente de los enemigos derrotados, el tiempo utilizado (solo se cuenta el usado para llenar el portal) y los golpes recibidos de forma que es directamente proporcional a lo primero e inversamente proporcional a los dos últimos factores.

# **Interfaz**

A continuación se especificarán las características de los menús e interfaces presentes en el juego. Se hará siguiendo el bucle de juego.

**1. Menú principal**

El menú es claro y sencillo. Incluirá el título del juego y el nombre del estudio así como 4 botones: Jugar, Salir, Opciones y Albúm.

![titleScreen](https://github.com/UCM-FDI-DISIA/nullptr/blob/main/docs/images/newTitle.png)

Si hay una partida guardada, aparecerá la opción de cargarla.

![titleScreen](https://github.com/UCM-FDI-DISIA/nullptr/blob/main/docs/images/newTitle2.png)

**2. Opciones**

En este menú, el jugador podrá cambiar los controles y ajustar el volumen a su gusto. Cuenta con una imagen donde se detallarán los controles y cada uno con dos botones para cambiar la opción indicada.

![options](https://github.com/UCM-FDI-DISIA/nullptr/blob/main/docs/images/newOptions.png)

**3. Albúm**

Espacio donde se podrán encontrar las características de las cartas encontradas en las diferentes sesiones de juego. Se podrán visualizar de manera general todas y, para observarlas con más detalle, hará falta seleccionarlas.

![album](https://github.com/UCM-FDI-DISIA/nullptr/blob/main/docs/images/newAlbum.png)

**4. Tutorial** 

Al darle al botón de _JUGAR_ entraremos al tutorial donde se explicarán los conocimientos básicos para poder disfrutar del juego.

![tutorial](https://github.com/UCM-FDI-DISIA/nullptr/blob/main/docs/images/newTutorial.png)

![tutorial2](https://github.com/UCM-FDI-DISIA/nullptr/blob/main/docs/images/newTutorial2.png)

**5. Bucle de juego** 

Tras pasarnos el tutorial, se generará un mapa aleatorio y se le presentará de la misma manera que en la imagen siguiente. Contiene 3 botones: uno para salir al menú principal, otro del Inventario del jugador y por último, el de opciones.

![gameLoop](https://github.com/UCM-FDI-DISIA/nullptr/blob/main/docs/images/newMap.png)

**6. Inventario** 

En esta sección el jugador podrá observar los objetos encontrados, su cantidad de Tiempo actual (monedas actuales), sus estadísticas ya modificadas por los objetos y gestionar el mazo de juego de cada batalla.
Podemos observar todos los elementos en la siguiente imagen donde la sección amarilla corresponde al inventario y la rojiza al mazo.

![inventory](https://github.com/UCM-FDI-DISIA/nullptr/blob/main/docs/images/newInventory.png)

**7. Combate (HUD)**

Durante el combate el HUD mostrará:
* <span style="text-decoration:underline;">Maná:</span> se mostrará una barra en la zona central superior izquierda con la cantidad de maná del jugador durante la partida.
* <span style="text-decoration:underline;">Carga de la máquina:</span> se mostrará la carga en un círculo que se irá rellenando en la zona central superior durante la partida.
* <span style="text-decoration:underline;">Vida:</span> se mostrará una barra en la zona superior central derecha con la vida actual del jugador.
* <span style="text-decoration:underline;">Mazo:</span> se mostrará el mazo en la esquina inferior izquierda.
* <span style="text-decoration:underline;">Mano:</span> se mostrarán en la zona inferior central las cartas de la mano. La seleccionada sobresaldrá más que el resto (ver imagen).
* <span style="text-decoration:underline;">Descarte:</span> se mostrará la pila de descartes en la esquina inferior derecha.

![HUD](https://github.com/UCM-FDI-DISIA/nullptr/blob/main/docs/images/newHud.png)

**8. Post-Combate**

Una pantalla que contiene las estadísticas durante la batalla: los enemigos derrotados, la vida perdida, el tiempo empleado, el dinero obtenido; y la obtención de nuevas cartas.

![postGame](https://github.com/UCM-FDI-DISIA/nullptr/blob/main/docs/images/newPostGame.png)

![postGame2](https://github.com/UCM-FDI-DISIA/nullptr/blob/main/docs/images/newPostGame2.png)

**9. Pausa**

El jugador podrá pausar el juego cuando esté en una batalla. En esta pantalla tendrá la oportunidad de ver su inventario, los controles y acceso a las opciones. Existirá también un botón que permitirá salir al menú principal y guardar el estado de la sesión de juego para que la próxima vez el jugador pueda continuar donde lo dejó.

![pause](https://github.com/UCM-FDI-DISIA/nullptr/blob/main/docs/images/newPause.png)

**10. Tienda**

Lugar donde el jugador podrá hacerse con hasta 4 nuevas cartas (una del pasado, una del presente, una del futuro y otra escogida al azar). El jugador podrá ver cuánto Tiempo tiene para poder comprar las cartas. Se podrán seleccionar las cartas para observar sus precios y se podrá clicar sobre el botón de _COMPRAR_ para efectuar la acción. Para acabar la fase de compra el jugador ha de clicar sobre el botón de _SALIR_.

![tienda](https://github.com/UCM-FDI-DISIA/nullptr/blob/main/docs/images/newShop.png)

**11. Cofre**

Aquí se entregará un objeto pasivo aleatorio al jugador. El jugador verá los atributos del objeto que le ha tocado. Tras esto, para avanzar al mapa debe seleccionar el botón _SALIR_.

![chest](https://github.com/UCM-FDI-DISIA/nullptr/blob/main/docs/images/newChest.png)

![chest2](https://github.com/UCM-FDI-DISIA/nullptr/blob/main/docs/images/newChest2.png)

## **Estadísticas**

**1. Personaje** {#1-personaje}

<table>
  <tr>
   <td><strong>Vida</strong>
   </td>
   <td>El máximo HP con el que se empieza cada combate
<p>
100 puntos de salud
   </td>
  </tr>
  <tr>
   <td><strong>Velocidad de movimiento</strong>
   </td>
   <td>La velocidad base con la que se empieza cada combate
<p>
100 unidades de velocidad
   </td>
  </tr>
  <tr>
   <td><strong>Ataque</strong>
   </td>
   <td>El daño base con la que se empieza cada combate sin importar si es ataque melee o a distancia
   </td>
  </tr>
  <tr>
   <td><strong>Velocidad de ataque</strong>
   </td>
   <td>La rapidez de ataque base del jugador con cualquier arma
<p>
1 atq/s
   </td>
  </tr>
  <tr>
   <td><strong>Maná</strong>
   </td>
   <td>La cantidad de maná máximo que puede tener el personaje
<p>
100 puntos de maná
   </td>
  </tr>
</table>

**2. Enemigos** {#2-enemigos}

<table>
  <tr>
   <td colspan="2" ><strong>Tanques</strong>
   </td>
  </tr>
  <tr>
   <td><strong>Vida</strong>
   </td>
   <td>60
   </td>
  </tr>
  <tr>
   <td><strong>Ataque</strong>
   </td>
   <td>Ataque a corta distancia.
<p>
Harán daño al jugador tanto por contacto como realizando un ataque en una pequeña área delante de él.
   </td>
  </tr>
  <tr>
   <td><strong>Vel. mov</strong>
   </td>
   <td>70 unidades de velocidad
   </td>
  </tr>
  <tr>
   <td><strong>Vel. ataq</strong>
   </td>
   <td>Lenta
   </td>
  </tr>
  <tr>
   <td><strong>Maná</strong>
   </td>
   <td>40
   </td>
  </tr>
  <tr>
   <td><strong>Carga máq.</strong>
   </td>
   <td>20
   </td>
  </tr>
  <tr>
   <td colspan="2" ><strong>Luchadores</strong>
   </td>
  </tr>
  <tr>
   <td><strong>Vida</strong>
   </td>
   <td>30
   </td>
  </tr>
  <tr>
   <td><strong>Ataque</strong>
   </td>
   <td>Ataque cuerpo a cuerpo.
<p>
Harán daño al jugador únicamente por contacto.
   </td>
  </tr>
  <tr>
   <td><strong>Vel. mov</strong>
   </td>
   <td>100 unidades de velocidad
   </td>
  </tr>
  <tr>
   <td><strong>Vel. ataq</strong>
   </td>
   <td>Rápida
   </td>
  </tr>
  <tr>
   <td><strong>Maná</strong>
   </td>
   <td>10
   </td>
  </tr>
  <tr>
   <td><strong>Carga máq.</strong>
   </td>
   <td>5
   </td>
  </tr>
  <tr>
   <td colspan="2" ><strong>Tiradores</strong>
   </td>
  </tr>
  <tr>
   <td><strong>Vida</strong>
   </td>
   <td>20
   </td>
  </tr>
  <tr>
   <td><strong>Ataque</strong>
   </td>
   <td>Ataque a distancia.
<p>
Harán daño al jugador con proyectiles disparados desde lejos.
   </td>
  </tr>
  <tr>
   <td><strong>Vel. mov</strong>
   </td>
   <td>90 unidades de velocidad
   </td>
  </tr>
  <tr>
   <td><strong>Vel. ataq</strong>
   </td>
   <td>Media
   </td>
  </tr>
  <tr>
   <td><strong>Maná</strong>
   </td>
   <td>20
   </td>
  </tr>
  <tr>
   <td><strong>Carga maq.</strong>
   </td>
   <td>10
   </td>
  </tr>
</table>

## **Objetos**

**1. Cartas**

Acceder al siguiente link para observar la tabla de información de las cartas: [cartas](https://docs.google.com/spreadsheets/d/19VJMATqT5oYdefOX2d9ag7M0UlijncVVMV4D1HyVSeI/edit?usp=share_link)

**2. Reliquias**

Acceder al siguiente link para observar la tabla de información de las reliquias: 

[reliquias](https://docs.google.com/spreadsheets/d/15Z0YxwjXVC0gQB7iJaG8bLAthahnz9QcRWQ3Nuaxg0E/edit?usp=sharing)


**1.  Estética**

Se seguirá una temática principal steampunk en el diseño principal del personaje y de los diferentes HUDs existentes.

**2. Historia**

La protagonista es una joven científica, una prodigio de su tiempo. 

Esta científica perdió a su esposa por una enfermedad para la que no había cura entonces y la pena de su pérdida le llevó a la idea de construir una máquina del tiempo para verla una última vez, ya que al terminar la máquina, la realidad desaparecerá a causa de las infinitas paradojas que esto generaría.

Esto ya se ha intentado en más ocasiones, pero solo destacan 2 personas por sobrevivir, una en 1494, por Leonardo Da Vinci, y otra por Marty McFly en 2552, pero fracasaron y se quedaron atrapados en esta dimensión, dejando rastros de su tiempo.

Ahora se dedican a vender cartas que encuentran o inventan a las pobres almas que cometen el error de intentar lo mismo para sobrevivir.

Es por esto que el guardián del tiempo, un horror cósmico de tres ojos, los cuales ven el pasado, presente y futuro, llamado Kronón lleva a la protagonista y su máquina imperfecta a su dimensión en la que el tiempo está entremezclado y no tiene sentido para evitar que la termine, pero la científica usará todo lo que esté en su mano para terminar la máquina.

Al llegar a Kronón y derrotar a este, la protagonista le quitará un ojo y la máquina del tiempo se sobrecargará, sacándola de esta dimensión a la realidad y destruyéndose en el proceso, por lo que tendrá que reconstruirla, lo que le llevará tiempo (envejecerá). Tiene que repetir este proceso dos veces más para conseguir todos los ojos y que la máquina se pueda controlar, siendo totalmente operativa y logrando el objetivo de la protagonista.

Las cartas son un invento del futuro que materializan armas y permiten usar habilidades o dar beneficios superhumanos.

**Reglas temporales (nuestras):**
* El tiempo NO DEBE ser alterado, por ello existe _Kronón _el guardián del tiempo. Al ser el guardián no puede eliminar a la protagonista de la historia matando a ningún antepasado, y por la misma razón, cada persona que entra en la dimensión de _Kronón _sale de ella en el mismo momento de la historia del que se fue.
* En la dimensión de _Kronón _ el tiempo es estable, no avanza. Por ello la protagonista no sufre ningún cambio físico aunque esté atrapada mucho tiempo.
* No pueden existir 2 versiones de la misma persona a la vez en el tiempo, de ahí que se intente evitar la creación de la máquina del tiempo. Esto crea una paradoja, y esta hará colapsar el universo.

**3. Paleta de colores**

![palette](https://github.com/UCM-FDI-DISIA/nullptr/blob/main/docs/images/newPalette.png)

**4. Bocetos**

![draftBoss](https://github.com/UCM-FDI-DISIA/nullptr/blob/main/docs/images/draftBoss.png)

![draftBoss2](https://github.com/UCM-FDI-DISIA/nullptr/blob/main/docs/images/draftBoss2.png)


![draftCardIdea](https://github.com/UCM-FDI-DISIA/nullptr/blob/main/docs/images/draftCardIdea.png)

![draftCardIdea2](https://github.com/UCM-FDI-DISIA/nullptr/blob/main/docs/images/draftCardIdea2.png)
	
![draftFinalCinematic](https://github.com/UCM-FDI-DISIA/nullptr/blob/main/docs/images/draftFinalCinematic.png)

## **Inspiraciones**
1. _The Binding of Isaac._ (2014) Nicalis Inc.
2. _Brotato._ (2022) Blobfish.
3. _Vampire Survivors._ (2022) Poncle.
4. _Slay the Spire._ (2019) Mega Crit Games.
5. _Neon White._ (2022) Annapurna Interactive.
6. _Risk of Rain 2._ (2020) Gearbox Publishing.
7. _Clash Royale._ (2016) Supercell.