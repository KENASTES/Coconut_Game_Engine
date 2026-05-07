#include "Sprite_Renderer.h"
#include <cstddef>

Sprite_Renderer::Sprite_Renderer() {
    Vertex Verticles[] = {
        {{ 1.0f,  1.0f, 0.0f},   {1.0f, 1.0f}},
        {{ 1.0f,  0.0f, 0.0f},   {1.0f, 0.0f}},
        {{ 0.0f,  0.0f, 0.0f},   {0.0f, 0.0f}},
        {{ 0.0f,  1.0f, 0.0f},   {0.0f, 1.0f}}
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Verticles), Verticles, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, TexCoord));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
};

void Sprite_Renderer::Set_Shader(GLuint shaderID) {
    Current_Shader_ID = shaderID;
};

void Sprite_Renderer::Draw() {
    glUseProgram(Current_Shader_ID);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
};

Sprite_Renderer::~Sprite_Renderer() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
};