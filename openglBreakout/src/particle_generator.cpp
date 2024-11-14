/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "particle_generator.h"
#include <iostream>
extern GladGLContext *gl;

ParticleGenerator::ParticleGenerator(Shader shader, Texture2D texture, unsigned int amount)
    : shader(shader), texture(texture), amount(amount)
{
    this->init();
}

void ParticleGenerator::Update(float dt, GameObject &object, unsigned int newParticles, glm::vec2 offset)
{
    // add new particles
    for (unsigned int i = 0; i < newParticles; ++i)
    {
        int unusedParticle = this->firstUnusedParticle();
        this->respawnParticle(this->particles[unusedParticle], object, offset);
    }
    // update all particles
    for (unsigned int i = 0; i < this->amount; ++i)
    {
        Particle &p = this->particles[i];
        p.Life -= dt; // reduce life
        if (p.Life > 0.0f)
        { // particle is alive, thus update
            p.Position -= p.Velocity * dt;
            p.Color.a -= dt * 2.5f;
        }
    }
}

// render all particles
void ParticleGenerator::Draw()
{
    // use additive blending to give it a 'glow' effect
    // gl->Disable(GL_DEPTH_TEST);
    gl->BlendFunc(GL_SRC_ALPHA, GL_ONE);
    this->shader.Use();
    // std::cout << "TM " << this->particles[0].Position.x << " " << this->particles[0].Position.y << " " << this->particles[0].Color.g << " " << this->particles[0].Color.r << " " << this->particles[0].Color.a << " " << this->particles[0].Life << std::endl;
    for (Particle particle : this->particles)
    {
        if (particle.Life > 0.0f)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(particle.Position, 0)); // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)
            // gl->PolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            this->shader.SetMatrix4("model", model);
            this->shader.Use().SetVector4f("clrr", particle.Color, true);
            // gl->ActiveTexture(GL_TEXTURE0);
            this->texture.Bind();
            gl->BindVertexArray(this->VAO);
            gl->DrawArrays(GL_TRIANGLES, 0, 6);
            gl->BindVertexArray(0);
        }
    }
    // don't forget to reset to default blending mode
    gl->BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // gl->Enable(GL_DEPTH_TEST);
}

void ParticleGenerator::init()
{
    // set up mesh and attribute properties
    unsigned int VBO;
    float particle_quad[] = {
        0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f};
    gl->GenVertexArrays(1, &this->VAO);
    gl->GenBuffers(1, &VBO);
    // fill mesh buffer
    gl->BindBuffer(GL_ARRAY_BUFFER, VBO);
    gl->BufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);

    gl->BindVertexArray(this->VAO);
    // set mesh attributes
    gl->EnableVertexAttribArray(0);
    gl->VertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);

    gl->BindBuffer(GL_ARRAY_BUFFER, 0);
    gl->BindVertexArray(0);

    // create this->amount default particle instances
    for (unsigned int i = 0; i < this->amount; ++i)
        this->particles.push_back(Particle());
}

// stores the index of the last particle used (for quick access to next dead particle)
unsigned int lastUsedParticle = 0;
unsigned int ParticleGenerator::firstUnusedParticle()
{
    // first search from last used particle, this will usually return almost instantly
    for (unsigned int i = lastUsedParticle; i < this->amount; ++i)
    {
        if (this->particles[i].Life <= 0.0f)
        {
            lastUsedParticle = i;
            return i;
        }
    }
    // otherwise, do a linear search
    for (unsigned int i = 0; i < lastUsedParticle; ++i)
    {
        if (this->particles[i].Life <= 0.0f)
        {
            lastUsedParticle = i;
            return i;
        }
    }
    // all particles are taken, override the first one (note that if it repeatedly hits this case, more particles should be reserved)
    lastUsedParticle = 0;
    return 0;
}

void ParticleGenerator::respawnParticle(Particle &particle, GameObject &object, glm::vec2 offset)
{
    float randomx = ((rand() % 100) - 50) / 2000.0f;
    float randomy = ((rand() % 100) - 50) / 2000.0f;
    float rColor = 0.5f + ((rand() % 100) / 100.0f);
    // std::cout << "EED " << particle.Position.x << " " << particle.Position.y << std::endl;
    particle.Position = glm::vec2(object.Position.x + randomx, object.Position.y + randomy) + offset;
    particle.Color = glm::vec4(rColor, rColor, rColor, 2.0f);
    particle.Life = 1.0f;
    particle.Velocity = object.Velocity * 0.1f;
    // std::cout << "EFG " << object.Velocity.x << " " << object.Velocity.y << std::endl;
    // std::cout << "EFG " << particle.Velocity.x << " " << particle.Velocity.y << std::endl;
}