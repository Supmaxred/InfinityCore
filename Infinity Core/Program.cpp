#define uint int

//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include "a_math.h"
//#include "vector3.h"
//#include "vector2.h"
//
//int main()
//{
//    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
//    sf::CircleShape shape(100.f);
//    shape.setFillColor(sf::Color::Green);
//    vector2 normal(-1, -0.5);
//    normal = normal.normalized();
//    vector2 vel(1, 0);
//
//
//    sf::VertexArray lines(sf::Lines, 8);
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        normal = vector2((sf::Mouse::getPosition().x / 1920.) - 0.5, (sf::Mouse::getPosition().y / 1080.) - 0.5);
//        normal = normal.normalized();
//
//        lines[0].position = sf::Vector2f(500 + -normal.y * 250, 500 + normal.x * 250);
//        lines[1].position = sf::Vector2f(500 + normal.y * 250, 500 + -normal.x * 250);
//        lines[0].color = sf::Color(0, 0, 255);
//        lines[1].color = sf::Color(0, 0, 255);
//
//        lines[0 + 2].position = sf::Vector2f(500, 500);
//        lines[1 + 2].position = sf::Vector2f(500 + normal.x * 250, 500 + normal.y * 250);
//        lines[0 + 2].color = sf::Color(255, 255, 0);
//        lines[1 + 2].color = sf::Color(255, 255, 0);
//
//        lines[0 + 4].position = sf::Vector2f(500 - vel.x * 250, 500 - vel.y * 250);
//        lines[1 + 4].position = sf::Vector2f(500, 500);
//        lines[0 + 4].color = sf::Color(255, 0, 0);
//        lines[1 + 4].color = sf::Color(255, 0, 0);
//
//        vector2 ref = vector2::projectOnPlane(vel, normal);
//        //ref = ref.normalized();
//
//        lines[0 + 6].position = sf::Vector2f(500, 500);
//        lines[1 + 6].position = sf::Vector2f(500 + ref.x * 250, 500 + ref.y * 250);
//        lines[0 + 6].color = sf::Color(255, 0, 0);
//        lines[1 + 6].color = sf::Color(255, 0, 0);
//
//        window.clear();
//        window.draw(lines);
//        window.display();
//    }
//
//    return 0;
//}


#include <SFML/Graphics.hpp>
#include <iostream>
#include "Mathf.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Transitions.h"
#include <chrono>
#include <SFML/OpenGL.hpp>
#include "Engine.h"

//bool LineIntersection(const Vector2 &p1, const Vector2 &p2, const Vector2 &p3, const Vector2 &p4, Vector2 &result)
//{
//    float bx = p2.x - p1.x;
//    float by = p2.y - p1.y;
//    float dx = p4.x - p3.x;
//    float dy = p4.y - p3.y;
//    float bDotDPerp = bx * dy - by * dx;
//    if (bDotDPerp == 0)
//    {
//        return false;
//    }
//    float cx = p3.x - p1.x;
//    float cy = p3.y - p1.y;
//    float t = (cx * dy - cy * dx) / bDotDPerp;
//    if (t < 0 || t > 1)
//    {
//        return false;
//    }
//    float u = (cx * by - cy * bx) / bDotDPerp;
//    if (u < 0 || u > 1)
//    {
//        return false;
//    }
//
//    result.x = p1.x + t * bx;
//    result.y = p1.y + t * by;
//    return true;
//}

#include "TestGame.h"

int main()
{
    TestGame game = TestGame();

    game.Create("test");

    return 0;
}

//int main()
//{
//    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
//    sf::CircleShape shape(100.f);
//    shape.setFillColor(sf::Color::Green);
//    Vector2 normal(-1, -0.5);
//    normal = normal.Normalized();
//    Vector2 vel(1, 0);
//
//    float lsizes = 1000.;
//
//    sf::VertexArray lines(sf::LinesStrip, lsizes);
//    for (size_t i = 0; i < lsizes; i++)
//    {
//        lines[i].position = (Vector2(i / lsizes, Transitions::EaseInOutPower(i / lsizes, 100.) * -1.) * 800. + Vector2(0., 900.)).SFML();
//        lines[i].color = sf::Color(252, 50, 50, 255);
//        //std::cout << (Vector2(i / lsizes, Transitions::EaseInPower(i / lsizes, 5.) * -1.) * 200. + Vector2(200., 400.)).ToString() << std::endl;
//    }
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        Vector2 mousePos = Vector2(sf::Mouse::getPosition());
//        normal = Vector2(sf::Mouse::getPosition()) / Vector2(1920., 1080.) - 0.5;
//        normal = normal.Normalized();
//
//        window.clear();
//        window.draw(lines);
//        window.display();
//    }
//
//    return 0;
//}

//int main()
//{
//    
//    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
//    sf::CircleShape shape(100.f);
//    shape.setFillColor(sf::Color::Green);
//    Vector2 normal(-1, -0.5);
//    normal = normal.Normalized();
//    Vector2 vel(1, 0);
//
//    sf::VertexArray lines(sf::Lines, 4);
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        Vector2 mousePos = Vector2(sf::Mouse::getPosition());
//        normal = Vector2(sf::Mouse::getPosition()) / Vector2(1920., 1080.) - 0.5;
//        normal = normal.Normalized();
//
//        lines[0 + 0].position = sf::Vector2f(750, 750);
//        lines[1 + 0].position = sf::Vector2f(750, 250);
//        lines[0 + 0].color = sf::Color(0, 0, 255);
//        lines[1 + 0].color = sf::Color(0, 0, 255);
//
//        Vector2 ip;
//
//        if (LineIntersection(Vector2(250, 500), mousePos, Vector2(750, 750), Vector2(750, 250), ip))
//        {
//            lines[0 + 2].position = sf::Vector2f(250, 500);
//            lines[1 + 2].position = ip.SFML();
//            lines[0 + 2].color = sf::Color(255, 0, 0);
//            lines[1 + 2].color = sf::Color(255, 0, 0);
//        }
//        else
//        {
//            lines[0 + 2].position = sf::Vector2f(250, 500);
//            lines[1 + 2].position = mousePos.SFML();
//            lines[0 + 2].color = sf::Color(255, 0, 0);
//            lines[1 + 2].color = sf::Color(255, 0, 0);
//        }
//
//        window.clear();
//        window.draw(lines);
//        window.display();
//    }
//
//    return 0;
//}