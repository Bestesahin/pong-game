#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace sf;

int main()
{
    const unsigned int WIDTH = 900;
    const unsigned int HEIGHT = 600;
    const int WINNING_SCORE = 5;

    RenderWindow window(VideoMode(Vector2u(WIDTH, HEIGHT)), "Pong Oyunu");
    window.setFramerateLimit(60);

    RectangleShape leftPaddle(Vector2f(20.f, 120.f));
    leftPaddle.setPosition(Vector2f(40.f, 240.f));
    leftPaddle.setFillColor(Color::Cyan);

    RectangleShape rightPaddle(Vector2f(20.f, 120.f));
    rightPaddle.setPosition(Vector2f(840.f, 240.f));
    rightPaddle.setFillColor(Color::Red);

    CircleShape ball(12.f);
    ball.setPosition(Vector2f(444.f, 294.f));
    ball.setFillColor(Color::White);

    float paddleSpeed = 7.f;
    float ballSpeedX = 5.f;
    float ballSpeedY = 4.f;

    int leftScore = 0;
    int rightScore = 0;
    bool gameOver = false;

    Font font;
    if (!font.openFromFile("arial.ttf"))
    {
        std::cout << "arial.ttf bulunamadi. Proje klasorune arial.ttf koyun." << std::endl;
        return 0;
    }

    Text scoreText(font, "", 40);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(Vector2f(370.f, 20.f));

    Text infoText(font, "Sol: W/S     Sag: Yukari/Asagi     R: Yeniden Baslat", 20);
    infoText.setFillColor(Color::White);
    infoText.setPosition(Vector2f(190.f, 560.f));

    Text winnerText(font, "", 45);
    winnerText.setFillColor(Color::Yellow);
    winnerText.setPosition(Vector2f(220.f, 260.f));

    RectangleShape middleLine(Vector2f(4.f, 600.f));
    middleLine.setPosition(Vector2f(448.f, 0.f));
    middleLine.setFillColor(Color(120, 120, 120));

    auto resetBall = [&]()
    {
        ball.setPosition(Vector2f(444.f, 294.f));
        ballSpeedX = -ballSpeedX;
        ballSpeedY = 4.f;
    };

    auto resetGame = [&]()
    {
        leftScore = 0;
        rightScore = 0;
        gameOver = false;

        leftPaddle.setPosition(Vector2f(40.f, 240.f));
        rightPaddle.setPosition(Vector2f(840.f, 240.f));
        ball.setPosition(Vector2f(444.f, 294.f));

        ballSpeedX = 5.f;
        ballSpeedY = 4.f;
    };

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
            {
                window.close();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::R))
        {
            resetGame();
        }

        if (!gameOver)
        {
            if (Keyboard::isKeyPressed(Keyboard::Key::W) && leftPaddle.getPosition().y > 0)
                leftPaddle.move(Vector2f(0.f, -paddleSpeed));

            if (Keyboard::isKeyPressed(Keyboard::Key::S) && leftPaddle.getPosition().y + leftPaddle.getSize().y < HEIGHT)
                leftPaddle.move(Vector2f(0.f, paddleSpeed));

            if (Keyboard::isKeyPressed(Keyboard::Key::Up) && rightPaddle.getPosition().y > 0)
                rightPaddle.move(Vector2f(0.f, -paddleSpeed));

            if (Keyboard::isKeyPressed(Keyboard::Key::Down) && rightPaddle.getPosition().y + rightPaddle.getSize().y < HEIGHT)
                rightPaddle.move(Vector2f(0.f, paddleSpeed));

            ball.move(Vector2f(ballSpeedX, ballSpeedY));

            if (ball.getPosition().y <= 0 || ball.getPosition().y + ball.getRadius() * 2 >= HEIGHT)
            {
                ballSpeedY = -ballSpeedY;
            }

            if (ball.getGlobalBounds().findIntersection(leftPaddle.getGlobalBounds()).has_value())
            {
                ballSpeedX = std::abs(ballSpeedX);
                ballSpeedX *= 1.05f;

                float paddleCenter = leftPaddle.getPosition().y + leftPaddle.getSize().y / 2.f;
                float ballCenter = ball.getPosition().y + ball.getRadius();
                ballSpeedY = (ballCenter - paddleCenter) / 15.f;
            }

            if (ball.getGlobalBounds().findIntersection(rightPaddle.getGlobalBounds()).has_value())
            {
                ballSpeedX = -std::abs(ballSpeedX);
                ballSpeedX *= 1.05f;

                float paddleCenter = rightPaddle.getPosition().y + rightPaddle.getSize().y / 2.f;
                float ballCenter = ball.getPosition().y + ball.getRadius();
                ballSpeedY = (ballCenter - paddleCenter) / 15.f;
            }

            if (ball.getPosition().x < 0)
            {
                rightScore++;
                resetBall();
            }

            if (ball.getPosition().x > WIDTH)
            {
                leftScore++;
                resetBall();
            }

            if (leftScore >= WINNING_SCORE)
            {
                winnerText.setString("Sol Oyuncu Kazandi!");
                gameOver = true;
            }

            if (rightScore >= WINNING_SCORE)
            {
                winnerText.setString("Sag Oyuncu Kazandi!");
                gameOver = true;
            }
        }

        scoreText.setString(std::to_string(leftScore) + "       " + std::to_string(rightScore));

        window.clear(Color(20, 20, 60));
        window.draw(middleLine);
        window.draw(leftPaddle);
        window.draw(rightPaddle);
        window.draw(ball);
        window.draw(scoreText);
        window.draw(infoText);

        if (gameOver)
            window.draw(winnerText);

        window.display();
    }

    return 0;
}