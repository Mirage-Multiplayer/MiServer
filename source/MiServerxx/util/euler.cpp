#include <MiServerxx/util/euler.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

static constexpr float EPSILON = 0.00000202655792236328125f;

glm::vec3 mimp::util::GTAQuatResolve(float x, float y, float z, float w)
{
    glm::quat q(w, x, y, z);
    float temp = 2 * q.y * q.z - 2 * q.x * q.w;
    float rx, ry, rz;

    if (temp >= 1.0f - EPSILON)
    {
        rx = 90.0f;
        ry = -glm::degrees(atan2(glm::clamp(q.y, -1.0f, 1.0f), glm::clamp(q.w, -1.0f, 1.0f)));
        rz = -glm::degrees(atan2(glm::clamp(q.z, -1.0f, 1.0f), glm::clamp(q.w, -1.0f, 1.0f)));
    }
    else if (-temp >= 1.0f - EPSILON)
    {
        rx = -90.0f;
        ry = -glm::degrees(atan2(glm::clamp(q.y, -1.0f, 1.0f), glm::clamp(q.w, -1.0f, 1.0f)));
        rz = -glm::degrees(atan2(glm::clamp(q.z, -1.0f, 1.0f), glm::clamp(q.w, -1.0f, 1.0f)));
    }
    else
    {
        rx = glm::degrees(asin(glm::clamp(temp, -1.0f, 1.0f)));
        ry = -glm::degrees(atan2(glm::clamp(q.x * q.z + q.y * q.w, -1.0f, 1.0f), glm::clamp(0.5f - q.x * q.x - q.y * q.y, -1.0f, 1.0f)));
        rz = -glm::degrees(atan2(glm::clamp(q.x * q.y + q.z * q.w, -1.0f, 1.0f), glm::clamp(0.5f - q.x * q.x - q.z * q.z, -1.0f, 1.0f)));
    }

    return glm::mod(glm::vec3(rx, ry, rz), 360.0f);
}