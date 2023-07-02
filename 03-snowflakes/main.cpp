#include <GL/glut.h>
#include <vector>
#include "Segment.h"

const int MAX_ORDER = 100;

std::vector<Segment> snowflake;
std::vector<Segment> orders[MAX_ORDER + 1];
int order = 0;
bool isGenerating = false;

void writeText(std::string text, double x, double y)
{
    glRasterPos2d(x, y);
    for (const auto &c : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void display()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(5.0);

    // Draw each line segment in the snowflake
    glBegin(GL_LINES);
    for (const auto &s : snowflake)
    {
        glVertex2d(s.a_[0], s.a_[1]);
        glVertex2d(s.b_[0], s.b_[1]);
    }
    glEnd();

    // Display instructions and information on the window
    glRasterPos2d(-0.95, 0.9);
    std::string orderStr = "Order: " + std::to_string(order);
    writeText(orderStr, -0.95, 0.9);
    writeText("Use arrow keys to increase or decrease order", -0.7, -0.8);
    glFlush();
}

bool isDistanceLessThanPixel(cv::Vec2d p1, cv::Vec2d p2, int viewportWidth, int viewportHeight)
{
    double distance = sqrt(pow(p1[0] - p2[0], 2) + pow(p1[1] - p2[1], 2));
    double pixelSize = 2.0 / std::min(viewportWidth, viewportHeight);
    return distance < pixelSize;
}

void computeOrder(int order)
{
    orders[order].reserve(snowflake.size() * 4); // reserve space for the children
    for (const auto &s : snowflake)              // for each segment
    {
        const std::vector<Segment> &children = s.getChildren();                      // generate its children
        orders[order].insert(orders[order].end(), children.begin(), children.end()); // and save them to the appropriate order
    }
}

void loadOrder(int order)
{
    if (order > MAX_ORDER || order < 0)
    {
        return;
    }

    // should block keypresses if this function is still running from a previous keypress
    if (isGenerating)
    {
        return;
    }

    // start generating
    isGenerating = true;

    // if the size of a segment is less than a pixel just load the previous order
    if (isDistanceLessThanPixel(snowflake.back().a_, snowflake.back().b_, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)))
    {
        orders[order].assign(orders[order - 1].begin(), orders[order - 1].end());
    }
    else if (orders[order].empty()) // if we haven't already computed it, compute the next order
    {
        computeOrder(order);
    }

    // load the current order into the current snowflake
    snowflake.assign(orders[order].begin(), orders[order].end());

    // refresh display
    glutPostRedisplay();

    std::cout << "display order: " << order << std::endl;
    isGenerating = false;
}

void handleSpecialKeypress(int key, int x, int y)
{
    if (key == GLUT_KEY_RIGHT)
    {
        // increase order using right arrow
        loadOrder(++order);
    }
    if (key == GLUT_KEY_LEFT)
    {
        // decrease order using left arrow
        loadOrder(--order);
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Snowflake");
    glutSpecialFunc(handleSpecialKeypress);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutDisplayFunc(display);

    // base points of triangle
    cv::Vec2d a(-0.5, -0.4);
    cv::Vec2d b(0.5, -0.4);

    // calculate tip
    double len = cv::norm(a - b);
    double height = len * sqrt(3) / 2;
    cv::Vec2d c(0, -0.4 + height);

    // create segements of 0th order and add to snowflake
    Segment ab(a, b);
    Segment bc(b, c);
    Segment ca(c, a);
    snowflake.push_back(ab);
    snowflake.push_back(bc);
    snowflake.push_back(ca);

    // save order zero
    orders[0].assign(snowflake.begin(), snowflake.end());

    // start program
    glutMainLoop();
    return 0;
}
