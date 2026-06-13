/**
 * @file Mesh.h
 * @brief Declara las estructuras Mesh y Submesh utilizadas para almacenar geometría renderizable.
 * @ingroup rendering
 */
#pragma once

#include "Prerequisites.h"
#include "Buffer.h"
#include "MeshComponent.h"

class Device;

/**
 * @struct Submesh
 * @brief Porción geométrica renderizable con sus propios buffers GPU.
 *
 * Un Mesh puede estar compuesto por varios Submesh, cada uno con un
 * slot de material independiente. Esto permite renderizar modelos
 * con múltiples materiales sin duplicar la geometría.
 */
struct Submesh {

    /** Vertex Buffer almacenado en GPU. */
    Buffer vertexBuffer;

    /** Index Buffer almacenado en GPU. */
    Buffer indexBuffer;

    /** Cantidad total de índices del submesh. */
    unsigned int indexCount = 0;

    /** Índice inicial dentro del Index Buffer. */
    unsigned int startIndex = 0;

    /** Slot de material asociado al submesh. */
    unsigned int materialSlot = 0;
};

/**
 * @class Mesh
 * @brief Colección de Submesh listos para renderizado.
 *
 * Representa una malla compuesta por una o más submallas, cada una
 * con sus propios buffers en GPU y material asociado.
 *
 * Esta clase reemplaza el uso directo de colecciones de MeshComponent
 * dentro del pipeline de renderizado.
 */
class Mesh {
public:

    /**
     * @brief Obtiene la colección de submallas.
     *
     * @return Referencia al vector de submallas.
     */
    std::vector<Submesh>& getSubmeshes() { return m_submeshes; }

    /**
     * @brief Obtiene la colección de submallas en modo lectura.
     *
     * @return Referencia constante al vector de submallas.
     */
    const std::vector<Submesh>& getSubmeshes() const { return m_submeshes; }

    /**
     * @brief Construye un Mesh a partir de datos geométricos en CPU.
     *
     * Cada MeshComponent se convierte en un Submesh independiente con
     * su propio Vertex Buffer e Index Buffer.
     *
     * Los slots de material se asignan según el orden de aparición
     * de los componentes de entrada (0, 1, 2, ...).
     *
     * Si la creación de alguna submalla falla, ésta se omite mientras
     * que las demás continúan siendo procesadas.
     *
     * @param device Dispositivo Direct3D utilizado para crear los buffers.
     * @param components Lista de mallas generadas por ModelLoader.
     * @return Mesh listo para utilizarse durante el renderizado.
     */
    static Mesh buildFrom(
        Device& device,
        const std::vector<MeshComponent>& components);

    /**
     * @brief Libera todos los buffers GPU asociados al Mesh.
     *
     * Destruye los Vertex Buffer e Index Buffer de cada Submesh
     * y vacía la colección interna.
     */
    void destroy() {
        for (Submesh& sm : m_submeshes) {
            sm.vertexBuffer.destroy();
            sm.indexBuffer.destroy();
        }
        m_submeshes.clear();
    }

private:

    /** Lista de submallas que componen el Mesh. */
    std::vector<Submesh> m_submeshes;
};