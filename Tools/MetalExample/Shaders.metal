#include <metal_stdlib>
using namespace metal;

struct Vertex {
    float4 position [[position]];
    float4 color;
};

vertex Vertex vertex_main(uint vertexID [[vertex_id]]) {
    float4 positions[3] = {
        float4(0.0, 0.5, 0.0, 1.0),
        float4(-0.5, -0.5, 0.0, 1.0),
        float4(0.5, -0.5, 0.0, 1.0)
    };

    float4 colors[3] = {
        float4(1.0, 0.0, 0.0, 1.0),
        float4(0.0, 1.0, 0.0, 1.0),
        float4(0.0, 0.0, 1.0, 1.0)
    };

    Vertex out;
    out.position = positions[vertexID];
    out.color = colors[vertexID];
    return out;
}

fragment float4 fragment_main(Vertex in [[stage_in]]) {
    return in.color;
}
