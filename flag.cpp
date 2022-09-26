
#include <string.h>

#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include <iostream>

using namespace std;
void drawCircleFillFan(float cx, float cy, float r, int num_segments)
{
	float theta = 3.1415926 * 2 / float(num_segments);
	float tangetial_factor = tanf(theta);//calculate the tangential factor 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	float radial_factor = cosf(theta);//calculate the radial factor 

	float x = r;//we start at angle = 0 

	float y = 0;

	glBegin(GL_TRIANGLE_STRIP);
	for (int ii = 0; ii < num_segments; ii++)
	{
		glVertex2f(x + cx, y + cy);//output vertex 

		float tx = -y;
		float ty = x;

		x += tx * tangetial_factor;
		y += ty * tangetial_factor;

		x *= radial_factor;
		y *= radial_factor;
	}
	glEnd();
}
void drawCircleFill(float cx, float cy, float r, int num_segments)
{
	float theta = 3.1415926 * 2 / float(num_segments);
	float tangetial_factor = tanf(theta);//calculate the tangential factor 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	float radial_factor = cosf(theta);//calculate the radial factor 

	float x = r;//we start at angle = 0 

	float y = 0;

	glBegin(GL_POLYGON);
	for (int ii = 0; ii < num_segments; ii++)
	{
		glVertex2f(x + cx, y + cy);//output vertex 

		float tx = -y;
		float ty = x;

		x += tx * tangetial_factor;
		y += ty * tangetial_factor;

		x *= radial_factor;
		y *= radial_factor;
	}
	glEnd();
}
void render_loop(GLfloat ww, GLfloat wh)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*glPointSize(10);
	glLineWidth(2.5);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex3f(10.0, 10.0, 0.0);
	glVertex3f(200.0, 10.0, 0.0);
	glVertex3f(200.0, 200.0, 0.0);
	glVertex3f(200.0, 10.0, 0.0);
	glEnd();
	*/
	unsigned int rgba = 0x00401Aff; // greeen, no alpha
	double x = ww/4;
	double y = 0;
	double w = ww - x;
	double h = wh;
	double cresrad = 120;
	glBegin(GL_QUADS);
	glColor4f(((rgba >> 24) & 0xff) / 255.0f,
		((rgba >> 16) & 0xff) / 255.0f,
		((rgba >> 8) & 0xff) / 255.0f,
		(rgba & 0xff) / 255.0f);
	glVertex3f(x, y, 0);
	glVertex3f(x + w, y, 0);
	glVertex3f(x + w, y + h, 0);
	glVertex3f(x, y + h, 0);
	glEnd();
	glColor4f(1, 1, 1, 1);
	glColor3f(1.0f, 1.0f, 1.0f); //white
	drawCircleFill(w/2+x, wh/2, cresrad, 360);
	glColor4f(((rgba >> 24) & 0xff) / 255.0f,
		((rgba >> 16) & 0xff) / 255.0f,
		((rgba >> 8) & 0xff) / 255.0f,
		(rgba & 0xff) / 255.0f);; //green
	drawCircleFill(w/2+x+35, wh/2+35, cresrad, 360);
	glColor4f(0, 0, 0, 1);
	drawCircleFill(w / 2 + x + 60, wh / 2 + 50, cresrad /3, 5);
	glColor4f(1, 1, 1, 1);
	drawCircleFill(w / 2 + x + 60, wh / 2 + 50, cresrad / 6, 5);
	/*glBegin(GL_TRIANGLE_FAN) {
	
	}
	*/

}


/* program entry */
int main(int argc, char* argv[])
{
	GLFWwindow* window;
	int width = 680;
	int height = 420;
	if (!glfwInit())
	{
		cout << "Fail" << endl;
		return 0;
	}

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}


	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// set up view
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// see https://www.opengl.org/sdk/docs/man2/xhtml/glOrtho.xml
	glOrtho(0.0, width, 0.0, height, 0.0, 1.0); // this creates a canvas you can do 2D drawing on


	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// Draw gears
		render_loop(width, height);
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Terminate GLFW
	glfwTerminate();
	return 0;

}