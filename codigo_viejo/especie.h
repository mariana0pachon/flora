#ifndef especie_h
#define especie_h

class Especie {
public:
  int nivel;
  String estadoNivel;

  bool nivelTerminado(int n) {
    return nivel == n && estadoNivel == "end";
  }

  void empezarNivel(int nuevoNivel) {
    nivel = nuevoNivel;
    estadoNivel = "start";
  }

  void terminarNivel() {
    estadoNivel = "end";
  }

  void verDatos() {
    Serial.print("Nivel: ");
    Serial.println(nivel);
    Serial.print("Estado del Nivel: ");
    Serial.println(estadoNivel);
  }
};

#endif
