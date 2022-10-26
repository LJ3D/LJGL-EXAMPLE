#include <ljgl.hpp>


int main(){
    // Take user input for the object to load
    std::string objToLoad;
    std::cout << "Enter the object to load: ";
    std::cin >> objToLoad;

    // === Set up a GLFW window, and init GLAD ===
    char windowName[] = "3D spinning object";
    GLFWwindow* window = LJGL::setup(windowName); // Setup function exists just to move all the boilerplate crap out of sight
    glEnable(GL_DEPTH_TEST); // Enable depth testing - emsures that objects are drawn in the right order
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Enable wireframe for model debugging
    
    LJGL::model_EBO object;
    object.readVBO(objToLoad + ".vbo");
    object.readEBO(objToLoad + ".ebo");
    object.m_shader.createShader("GLSL/shader.vert.glsl", "GLSL/shader.frag.glsl");
    object.m_shader.setUniform3f("lightPos", 1.0f, 10.0f, 2.0f);

    // === Define transforms ===
    // === perspective/view transforms:
    int m_viewport[4]; // Stores the viewport size
    glGetIntegerv(GL_VIEWPORT, m_viewport); // Gets the viewport size
    glm::mat4 perspective = glm::perspective(glm::radians(45.0f), (float)m_viewport[2] / (float)m_viewport[3], 0.1f, 100.0f); // Define the perspective projection matrix
    glm::mat4 view = glm::mat4(1.0f); // Define a view matrix for the scene
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f)); // note that we're translating the scene in the reverse direction of where we want to move
    // Only need to set this transform once (camera never moves in this example), so lets do it now outside of the loop:
    object.setViewT(view);
    glm::mat4 model = glm::mat4(1.0f); // Define a model matrix for the square

    // === Main loop === //
    while (!glfwWindowShouldClose(window)){
        // === Unbind/reset stuff (best practice or something) ===
        glUseProgram(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // === Render ===
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Set the background color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color and depth buffer

        // Set up the perspective projection matrix to ensure that the suzanne is rendered correctly if the window is resized:
        glGetIntegerv(GL_VIEWPORT, m_viewport); // Get the viewport size (maybe code to only do upon resize? - would required messy global variables)
        perspective = glm::perspective(glm::radians(45.0f), (float)m_viewport[2] / (float)m_viewport[3], 0.1f, 100.0f); // Update the perspective projection matrix
        object.setProjectionT(perspective); // Set the perspective projection matrix

        // Rotate and draw the suzanne :D
        model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.5f)); // Rotate the suzanne
        object.setModelT(model); // Set the model matrix
        object.draw();

        // === Swap buffers ===
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}