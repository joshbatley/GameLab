#include "Camera.h"

bool checkIntersection(const glm::imat4x2 &square1, const glm::imat4x2 &square2)
{
    int minX1 = square1[0].x;
    int maxX1 = square1[1].x;
    int minY1 = square1[0].y;
    int maxY1 = square1[2].y;

    int minX2 = square2[0].x;
    int maxX2 = square2[1].x;
    int minY2 = square2[0].y;
    int maxY2 = square2[2].y;

    if ((minX1 <= minX2) && (maxX1 >= maxX2) && (minY1 <= minY2) && (maxY1 >= maxY2)) {
        return true;
    }

    bool overlapX = (minX1 < maxX2) && (maxX1 > minX2);
    bool overlapY = (minY1 < maxY2) && (maxY1 > minY2);


    if (overlapX && overlapY) {
        return true;
    }
    return false;
}

glm::vec4 OverlappedSquare(const glm::imat4x2 &square1, const glm::imat4x2 &square2)
{
    int minX1 = square1[0].x;
    int maxX1 = square1[1].x;
    int minY1 = square1[0].y;
    int maxY1 = square1[2].y;

    int minX2 = square2[0].x;
    int maxX2 = square2[1].x;
    int minY2 = square2[0].y;
    int maxY2 = square2[2].y;

    int overlapX = std::max(minX1, minX2);
    int overlapY = std::max(minY1, minY2);

    int overlapWidth = std::min(maxX1, maxX2) - overlapX;
    int overlapHeight = std::min(maxY1, maxY2) - overlapY;

    return glm::vec4 {overlapX, overlapY, overlapWidth, overlapHeight};
}

void GetVisibleEntities(Engine::World &world, Graphics::Handler &graphics)
{
    // Loop over all
    // get all visable
    // get size
    // apply texture/colour

    auto cameras = world.view<Camera, Transform, VisibleEntities>();
    auto sprites = world.view<Sprite, GlobalTransform>();
    for (auto [_, camera, transform, visibleEntities]: cameras.each()) {
        auto points = camera.cameraPoints(transform);

        visibleEntities.entities.clear();

        // Collect all visible.
        std::vector entities(sprites.begin(), sprites.end());
        std::ranges::sort(entities, [&world](const auto a, const auto b) {
            int l1 = 0;
            int l2 = 0;
            if (auto l = world.try_get<RenderLayer>(a)) {
                l1 = l->layer;
            }
            if (auto l = world.try_get<RenderLayer>(b)) {
                l2 = l->layer;
            }
            return l1 < l2;
        });

        for (auto entity: entities) {
            auto sprite = sprites.get<Sprite>(entity);
            auto spriteTransform = sprites.get<GlobalTransform>(entity);
            auto spritePoints = sprite.getAbsPoints(Transform {{spriteTransform.position.x, spriteTransform.position.y, 0}});

            if (checkIntersection(points, spritePoints)) {
                visibleEntities.entities.emplace_back(entity);
            }
        }
    }
}


void RenderSprites(Engine::World &world, Graphics::Handler &graphics)
{
    auto view = world.view<Camera, Transform, VisibleEntities>();
    for (auto [_, camera, cameraTransform, visibleEntities]: view.each()) {
        auto points = camera.cameraPoints(cameraTransform);

        for (auto entity: visibleEntities.entities) {
            auto sprite = world.get<Sprite>(entity);
            auto transform = world.get<GlobalTransform>(entity);
            auto spritePoints = sprite.getAbsPoints(Transform {{transform.position.x, transform.position.y, 0}});
            auto newSquare = OverlappedSquare(points, spritePoints);

            // glm::ivec4 pos {transformLocal.x, transformLocal.y, sprite.size.x, sprite.size.y};
            // graphics.DrawRectFill(sprite.color, pos);
            if (!world.all_of<Image>(entity)) {
                graphics.DrawRectFill(sprite.color, {newSquare.x, newSquare.y, newSquare.z, newSquare.w});
                continue;
            }
            auto image = world.get<Image>(entity);

            // left
            if (newSquare.x > transform.position.x) {
                auto rate = newSquare.z / sprite.size.x;
                sprite.srcSize.x += sprite.srcSize.z - (sprite.srcSize.z * (rate));
                sprite.srcSize.z -= sprite.srcSize.z - (sprite.srcSize.z * (rate));
            }

            // right
            if ((newSquare.x + newSquare.z) < (transform.position.x + sprite.size.x)) {
                auto rate = newSquare.z / sprite.size.x;
                sprite.srcSize.z -= sprite.srcSize.z - (sprite.srcSize.z * (rate));
            }

            // up
            if (newSquare.y > transform.position.y) {
                auto rate = newSquare.w / sprite.size.y;
                sprite.srcSize.y += sprite.srcSize.w - (sprite.srcSize.w * (rate));
                sprite.srcSize.w -= sprite.srcSize.w - (sprite.srcSize.w * (rate));
            }

            // down
            if ((newSquare.y + newSquare.w) < (transform.position.y + sprite.size.y)) {
                auto rate = newSquare.w / sprite.size.y;
                sprite.srcSize.w -= sprite.srcSize.w - (sprite.srcSize.w * (rate));
            }

            graphics.Render(image.texture, sprite.srcSize, newSquare);
        }
    }
}


void RenderGizmos(Engine::World &world, Graphics::Handler &graphics)
{
    auto cameras = world.view<Camera, Transform, VisibleEntities>();
    for (auto [_, camera, transform, visibleEntities]: cameras.each()) {
        auto lines = world.view<Line>();
        for (auto lineEnt: lines) {
            auto line = world.get<Line>(lineEnt);
            // Apply view port

            auto start = camera.worldspaceToViewPort(transform.position, {line.start.x, line.start.y, 0});
            auto end = camera.worldspaceToViewPort(transform.position, {line.end.x, line.end.y, 0});
            graphics.DrawLine(line.color, {start.x, start.y}, {end.x, end.y});
        }
    }
}