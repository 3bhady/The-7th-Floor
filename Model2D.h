//
// Created by mohamed on 16/12/16.
//
#ifndef JUNG_MODEL2D_H
#define JUNG_MODEL2D_H
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <SOIL/SOIL.h>

#include <glm/gtx/euler_angles.hpp>
#pragma once
// Std. Includes
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include "Shader.h"




class Model2D {
public:
    std::string tag;
    glm::mat4 modelMatrix = glm::mat4(1.0);
    float vertices[9] = {
            -1.0f,0.0f,0.0f,
            1.0f,0.0f,0.0f,



    };

    GLuint VBOs, VAOs;
    Model2D(std::string string) {
        tag=string;
        modelMatrix=glm::rotate(glm::mat4(1.0),glm::radians(30.0f),glm::vec3(0,0,1.0))*modelMatrix;
        modelMatrix=glm::translate(glm::mat4(1.0),glm::vec3(0.2f,0.2f,0.0))*modelMatrix;

    }
    void Draw(Shader* shader){
        GLuint VBOs, VAOs;
        glGenVertexArrays(1,& VAOs); // We can also generate multiple VAOs or buffers at the same time
        glGenBuffers(1, &VBOs);
        // ================================
        // First Triangle setup
        // ===============================
        glBindVertexArray(VAOs);
       GLuint transformLoc = glGetUniformLocation(shader->Program, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glBindBuffer(GL_ARRAY_BUFFER, VBOs);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
        glBindVertexArray(VAOs);
        glDrawArrays(GL_LINES, 0, 2);
    }

};


#endif //JUNG_MODEL2D_H
