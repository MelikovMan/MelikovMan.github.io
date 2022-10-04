

#include <string.h>

#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include <iostream>
#include <vector>

using namespace std;
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
vector<pair<float,float>> drawCircleFillRet(float cx, float cy, float r, int num_segments, float startdegree)
{	
	vector<pair<float, float>> coor;
	float theta = 3.1415926 * 2 / float(num_segments);
	float tangetial_factor = tanf(theta);//calculate the tangential factor 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	float radial_factor = cosf(theta);//calculate the radial factor 

	float x = r * cosf(startdegree * 3.1415926 / 180);//we start at angle = startdegree

	float y = r * sinf(startdegree * 3.1415926 / 180);

	glBegin(GL_POLYGON);
	for (int ii = 0; ii < num_segments; ii++)
	{
		coor.push_back(make_pair(x + cx, y + cy));
		glVertex2f(x + cx, y + cy);//output vertex 

		float tx = -y;
		float ty = x;

		x += tx * tangetial_factor;
		y += ty * tangetial_factor;

		x *= radial_factor;
		y *= radial_factor;
	}
	glEnd();
	return coor;
}
void render_loop(GLfloat ww, GLfloat wh, float delta)
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
	double x = ww / 4;
	double y = 0;
	double w = ww - x;
	double h = wh;
	double cresrad = 130;
	int vertices = 5;
	float alpharotation = 8+delta;
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
	drawCircleFill(w / 2 + x, wh / 2, cresrad, 360);
	glColor4f(((rgba >> 24) & 0xff) / 255.0f,
		((rgba >> 16) & 0xff) / 255.0f,
		((rgba >> 8) & 0xff) / 255.0f,
		(rgba & 0xff) / 255.0f); //green
	drawCircleFill(w / 2 + x + 38, wh / 2 + 32, cresrad-7, 360);
	vector<pair<float, float>> polygonInner, polygonOuter;
	//glColor4f(1, 0, 1, 1);
	polygonOuter = drawCircleFillRet(w / 2 + x + 50, wh / 2 + 60, cresrad / 3.3, vertices, (180/vertices) + alpharotation/2);
	glColor4f(1, 1, 1, 1);
	polygonInner = drawCircleFillRet(w / 2 + x + 50, wh / 2 + 60, cresrad / 8.8, vertices, 0 + alpharotation);
	/*if (debug) {
		for (pair<float, float> p1 : polygonInner) {
			cout << p1.first << " " << p1.second << endl;
		}
		for (pair<float, float> p1 : polygonOuter) {
			cout << p1.first << " " << p1.second << endl;
		}
	}
	*/
	for (int i = 1; i < vertices+1; i++) {
		glBegin(GL_TRIANGLES);
		glColor4f(1, 1, 1, 1);
		glVertex3f(polygonOuter.at(i % vertices).first, polygonOuter.at(i % vertices).second, 0);
		glVertex3f(polygonInner.at((i + 1) % vertices).first, polygonInner.at((i + 1) % vertices).second, 0);
		glVertex3f(polygonInner.at((i - 1) % vertices).first, polygonInner.at((i - 1 )% vertices).second, 0);
		glEnd();
	}
}


/* program entry */
int main(int argc, char* argv[])
{
	bool debug = 1;
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
	float deltaalpha = 0;
	while (!glfwWindowShouldClose(window))
	{
		// Draw gears
		render_loop(width, height, deltaalpha);
		//deltaalpha += 1;
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Terminate GLFW
	glfwTerminate();
	return 0;

}