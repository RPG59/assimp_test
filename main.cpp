#define GLEW_STATIC

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "glew.h"
#include "glfw3.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <mat4x4.hpp>
#include <vec3.hpp>
#include <gtc/matrix_transform.hpp>
#include <cmath>

struct vec3 {
    float x;
    float y;
    float z;
};

const char *VS = "#version 330\n"
                 "layout(location=0) in vec4 a_Pos;\n"
                 "uniform mat4 view;\n"
                 "uniform mat4 proj;\n"
                 "void main() {\n"
                 "  gl_Position = proj * view * a_Pos;\n"
                 "}\n";

const char *FS = "#version 330\n"
                 "out vec4 fragColor;\n"
                 "void main() {\n"
                 "  fragColor = vec4(.1, .2, .2, 1.);\n"
                 "}\n";

int main() {
    Assimp::Importer importer;
    const std::string objPath = "C:\\Dev\\web\\RPGFgin\\sanbox\\LP1.obj";
    const aiScene *scene = importer.ReadFile(objPath,
                                             aiProcess_Triangulate |
                                             aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR: Scene is not created" << std::endl;
    }

    std::cout << scene->mNumMeshes << std::endl;
    aiMesh *p_mesh = scene->mMeshes[0];
    std::cout << p_mesh->mNumVertices << std::endl;


//    std::vector<vec3> vertices = {{.5, .5, 0}, {.5, -.5, 0}, {-.5, -.5, 0}, {-.5, .5, 0}};
//    std::vector<uint32_t> indices = {0, 1, 3, 1, 2, 3};
    std::vector<vec3> vertices;
    std::vector<uint32_t> indices;

    for (uint32_t i = 0; i < p_mesh->mNumVertices; ++i) {
        vec3 vert;
        vert.x = p_mesh->mVertices[i].x;
        vert.y = p_mesh->mVertices[i].y;
        vert.z = p_mesh->mVertices[i].z;
        vertices.push_back(vert);
    }

    for (uint32_t i = 0; i < p_mesh->mNumFaces; ++i) {
        aiFace face = p_mesh->mFaces[i];
        for (uint32_t j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }

    std::cout << "VERTICES: " << vertices.size() << std::endl;
    std::cout << "INDICES: " << indices.size() << std::endl;


    if (!glfwInit()) {
        std::cout << "GLFW is not ok!" << std::endl;
    }
    GLFWwindow *window = nullptr;
    window = glfwCreateWindow(1024, 768, "test", nullptr, nullptr);


    if (window == nullptr) {
        std::cout << "Window is not created" << std::endl;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW is not ok!" << std::endl;
    }

    uint32_t VBO;
    uint32_t EBO;

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    const uint32_t vsId = glCreateShader(GL_VERTEX_SHADER);
    const uint32_t fsId = glCreateShader(GL_FRAGMENT_SHADER);
    uint32_t program = glCreateProgram();
    int compileStatus;
    glShaderSource(vsId, 1, &VS, nullptr);
    glShaderSource(fsId, 1, &FS, nullptr);
    glCompileShader(vsId);
    glGetShaderiv(vsId, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus != GL_TRUE) {
        std::cout << "VS compile error" << std::endl;
    }
    glCompileShader(fsId);
    glGetShaderiv(fsId, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus != GL_TRUE) {
        std::cout << "FS compile error" << std::endl;
    }

    glAttachShader(program, vsId);
    glAttachShader(program, fsId);
    glValidateProgram(program);
    glLinkProgram(program);
    glDeleteShader(vsId);
    glDeleteShader(fsId);

    glUseProgram(program);
    int t = 0;

    glm::mat4x4 projection = glm::perspective(glm::radians(90.), 4. / 3., .1, 100.);

    glm::mat4x4 view = glm::lookAt(glm::vec3(std::cos(t / 100.), -2, std::sin(t / 100.)), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    int projLocation = glGetUniformLocation(program, "proj");
    glUniformMatrix4fv(0, 1, 0, &view[0][0]);
    glUniformMatrix4fv(projLocation, 1, 0, &projection[0][0]);




    while (!glfwWindowShouldClose(window)) {
        view = glm::lookAt(glm::vec3(std::cos(t / 100.), 1, std::sin(t / 100.)), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        glUniformMatrix4fv(0, 1, 0, &view[0][0]);
        ++t;
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1, 1, .5, 1.);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    return 0;
}
