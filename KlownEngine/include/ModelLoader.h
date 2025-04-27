#pragma once
#include  "Prerequisites.h"
#include  "MeshComponent.h"
#include "fbxsdk.h"

struct LoadDataOBJ {
  std::string name;
  std::vector<SimpleVertex> vertex;
  std::vector<unsigned int> index;
  int numVertex = 0;
  int numIndex = 0;
};

class
ModelLoader {
public:
  /**
   * @brief Destructor y Contructor por defecto
   */
  ModelLoader() = default;
  ~ModelLoader() = default;

  /**
   * @brief Inicializa el FBX Manager, las configuraciones de entrada/salida, y crea una nueva escena.
 * @return true si la inicialización fue exitosa.
   */
  bool
  InitializeFBXManager();

  /**
   * @brief Carga un modelo FBX desde la ruta especificada y procesa su contenido.
   * @param filePath Ruta al archivo .fbx.
   * @return true si el modelo fue cargado exitosamente.
   */
  bool
  LoadFBXModel(const std::string& filePath);

  /**
   * @brief Procesa un nodo del grafo de escena FBX de forma recursiva.
   * @param node Puntero al nodo FBX a procesar.
   */
  void
  ProcessFBXNode(FbxNode* node);

  /**
   * @brief  Extrae nombres de archivos de texturas desde un material FBX.
   * @param material Material del que se extraerán los nombres.
 */
  void
  ProcessFBXMesh(FbxNode* node);

  /**
   * @brief Extrae vértices, índices y datos UV desde un nodo con malla.
   * @param node Nodo que contiene la malla.
   */
  void
  ProcessFBXMaterials(FbxSurfaceMaterial* material);

  /**
   * @brief Devuelve la lista de nombres de archivos de texturas cargadas del FBX.
   */
  std::vector<std::string>
  GetTextureFileNames() const { return textureFileNames; }

  /**
  * @brief Utiliza objl::Loader para cargar un archivo .obj y extraer los datos de malla.
  * @param filePath Ruta al archivo .obj.
  * @return true si el archivo fue cargado correctamente.
  */
  bool 
  LoadOBJ_model(const std::string& filePath);

  /**
   * @brief Carga un archivo .obj y devuelve la información como una estructura LoadDataOBJ.
   * @param objFileName Ruta del archivo .obj.
   * @return Estructura con datos de vértices e índices.
   */
  LoadDataOBJ
  LoadOBJ(std::string objFileName);

private:
  FbxManager* lSdkManager;
  FbxScene* lScene;
  std::vector<std::string> textureFileNames;
public:
  std::vector<MeshComponent> meshes;
};