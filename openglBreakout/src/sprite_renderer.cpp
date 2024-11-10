/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "sprite_renderer.h"
extern GladGLContext *gl;

SpriteRenderer::SpriteRenderer(const Shader &shader)
{
    this->shader = shader;
    this->initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
    gl->DeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::DrawSprite(const Texture2D &texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
{
    // prepare transformations
    this->shader.Use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f)); // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));   // move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));  // then rotate
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back

    model = glm::scale(model, glm::vec3(size, 1.0f)); // last scale

    this->shader.SetMatrix4("model", model);

    // render textured quad
    this->shader.SetVector3f("spriteColor", color);

    gl->ActiveTexture(GL_TEXTURE0);
    texture.Bind();

    gl->BindVertexArray(this->quadVAO);
    gl->DrawArrays(GL_TRIANGLES, 0, 6);
    gl->BindVertexArray(0);
}

void SpriteRenderer::initRenderData()
{
    // configure VAO/VBO
    unsigned int VBO;
    float vertices[] = {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f};

    gl->GenVertexArrays(1, &this->quadVAO);
    gl->GenBuffers(1, &VBO);

    gl->BindBuffer(GL_ARRAY_BUFFER, VBO);
    gl->BufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    gl->BindVertexArray(this->quadVAO);
    gl->EnableVertexAttribArray(0);
    gl->VertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    gl->BindBuffer(GL_ARRAY_BUFFER, 0);
    gl->BindVertexArray(0);
}