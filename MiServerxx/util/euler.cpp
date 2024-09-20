#include <MiServerxx/util/euler.hpp>

float mimp::util::quaternionToYaw(float x, float y, float z, float w)
{
    // Calcular Yaw (em torno do eixo Y)
    float siny_cosp = 2.0f * (w * y + z * x);
    float cosy_cosp = 1.0f - 2.0f * (y * y + x * x);
    return std::atan2(siny_cosp, cosy_cosp); // Retorna o ângulo Yaw
}