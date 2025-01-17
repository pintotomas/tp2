Padron: 98757

Nombre: Pinto Tomas Eduardo

Repositorio: https://github.com/pintotomas/tp2

## Descripcion

Para resolver el trabajo practico primero implemente una cola bloqueante donde el thread principal (Orchestator) se encarga de llenarla con recursos los cuales luego seran obtenidos por los recolectores. A la hora de hacer push y pop en la cola esta se bloquea para que los demas recolectores o el orchestator no la modifiquen mientras quien esta operando esta haciendo sus cambios. 

Cuando un recolector obtiene un recurso, este lo inserta en un inventario que tambien es protegido por un monitor, cada una de sus operaciones publicas, como en la cola bloqueante, son atomizadas mediante un lock. 

El monitor del inventario tambien es compartido con los productores, mientras los recolectores guardan recursos en el inventario, los productores los utilizan si encuentran la cantidad que necesitan. Donde se resuelven los posibles conflictos con los recolectores es en el metodo inventory_handle_requirements, que opera de la siguiente manera: 

1) Cuando instanciamos a un productor, inmediatamente se llama a este metodo para intentar obtener tantos recursos como necesite 

2) Si el inventario tiene los recursos necesarios, devuelve True al productor

3) Si no se tienen los recursos requeridos ni hay recolectores trabajando, se lanza una excepcion que debe manejar el productor

4) Si no se tienen los recursos requeridos pero aun hay recolectores trabajando, se pone a dormir al thread (Productor) mediante cv.wait(). 

5) El productor sera despertado si: 

	a) Se agregan nuevos recursos en el inventario 
	b) No hay mas recolectores trabajando

En ambos casos a) y b) se vuelve al paso 2). 

Una vez que el productor obtuvo los recursos que necesitaba (Obtiene un True de parte del InventoryMonitor) accede a un acumulador de puntos compartido por todos los trabajadores, que, nuevamente, debe ser protegido para evitar fallas mediante el uso de locks. Se atomiza la operacion de incrementar el contador de puntos, y, finalmente, cuando tanto recolectores y productores dejan de trabajar, el Orchestator muestra los recursos que no se utilizaron y cuantos puntos se obtuvieron por los recursos trabajados.
 
## Diagramas

![Diagrama de clases](diagramas/diagrama_de_clases.jpeg)

En este diagrama de clases omiti la clase Orchestator para que sea mas claro el diagrama y ademas no enriquece mucho lo que quiero mostrar.

![Diagrama de flujo recoleccion](diagramas/flujo_recolector.png)

En este diagrama muestro como un recolector toma recursos de la cola y los envia al inventario a traves de un monitor. Al no haber recursos en la cola y obviando que no esta cerrada, espera hasta que el Orchestator haga un push de un recurso a la cola para obtenerlo y asi devolverlo al recolector para finalizar su tarea.

![Diagrama de flujo produccion](diagramas/flujo_produccion.png)

En este diagrama muestro como un productor intenta obtener recursos a traves del monitor del inventario. En un principio, el inventario no tiene todos los recursos necesario por lo que hago que el thread espere hasta que luego se agrega un nuevo recurso, se notifica al thread (carpintero) para que vuelva a intentar obtener los recursos y al obtener una respuesta exitosa (se encuentran todos los recursos necesarios) se informa al productor y este suma puntos en un almacenador de puntos compartido.

Nota: Omiti la llamada a lock(mutex) al acceder al monitor para hacer al diagrama mas legible

## Aclaraciones

- Intente guardar tanto a los productores como a los recolectores en tan solo dos vectores, pero no logre que compilara mi solucion y decidi dejarlos en vectores separados a cada tipo de productor y recolector

## Correcciones

- Indentacion en firmas de funciones si las parto en multiples lineas para que sea mas legible

- Nombres de variables y metodos en un unico idioma (ingles)

- Pasaje por referencia en vez de punteros (o copias) en toda la aplicacion.

- El destructor hace el cerrado de las colas y join de los threads si no fue hecho anteriormente (lo hice de esta manera por el problema que comente en el [post de google groups](https://groups.google.com/forum/#!topic/tallerdeprogramacion/-UTyDwNuSkY))

- Uso std::move para devolver los vectores en vez de devolver una copia. Tambien los construyo in place

- Eliminacion de las variables globales de los mapas con los requisitos de cada productor. Ahora se inicializa en el constructor, evitando tambien su copia.

- El productor duerme antes de agregar los puntos