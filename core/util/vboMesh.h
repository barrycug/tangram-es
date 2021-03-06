#pragma once

#include <vector>

#include "vertexLayout.h"
#include "platform.h"

/*
 * VboMesh - Drawable collection of geometry contained in a vertex buffer and (optionally) an index buffer
 */

class VboMesh {

public:

    /*
     * Creates a VboMesh for vertex data arranged in the structure described by _vertexLayout to be drawn
     * using the OpenGL primitive type _drawMode
     */
    VboMesh(std::shared_ptr<VertexLayout> _vertexlayout, GLenum _drawMode = GL_TRIANGLES);
    
    
    /*
     * Destructs this VboMesh and releases all associated OpenGL resources
     */
    virtual ~VboMesh();

    /*
     * Adds a single vertex to the mesh; _vertex must be a pointer to the beginning of a vertex structured
     * according to the VertexLayout associated with this mesh
     */
    void addVertex(GLbyte* _vertex);

    /*
     * Adds _nVertices vertices to the mesh; _vertices must be a pointer to the beginning of a contiguous
     * block of _nVertices vertices structured according to the VertexLayout associated with this mesh
     */
    void addVertices(GLbyte* _vertices, int _nVertices);

    bool hasVertices() const { return m_nVertices > 0; };

    /*
     * Adds a single index to the mesh; indices are unsigned shorts
     */
    void addIndex(GLushort* _index);

    /*
     * Adds _nIndices indices to the mesh; _indices must be a pointer to the beginning of a contiguous
     * block of _nIndices unsigned short indices
     */
    void addIndices(GLushort* _indices, int _nIndices);

    bool hasIndices() const { return m_indices.size() > 0; };

    /*
     * Copies all added vertices and indices into OpenGL buffer objects; After geometry is uploaded,
     * no more vertices or indices can be added
     */
    void upload();

    /*
     * Renders the geometry in this mesh using the ShaderProgram _shader; if geometry has not already
     * been uploaded it will be uploaded at this point
     */
    void draw(std::shared_ptr<ShaderProgram> _shader);

private:

    std::shared_ptr<VertexLayout> m_vertexLayout;
    
    std::vector<GLbyte> m_vertexData; // Raw interleaved vertex data in the format specified by the vertex layout
    int m_nVertices;
    GLuint m_glVertexBuffer;

    std::vector<GLushort> m_indices;
    int m_nIndices;
    GLuint m_glIndexBuffer;

    GLenum m_drawMode;

    bool m_isUploaded;

};