---
icon: lucide/rocket
---


# Architecture
``` mermaid
flowchart TB
    A{"App"} --> B{"Rendering"} & C{"Base"}
    C--> File.h
    C--> Window.h
    B --> DX11["DX11"] & DX12["DX12"] & Vulkan["Vulkan"] & OpenGL["OpenGL"] & Metal["Metal"] & D{"Core"}
    D --> Shader.h["Shader.h"]
```


# Use Cases
 - VFX Applications
 - DCC Tools
 - Game Tools
 - Game Applications
# Problems FAQ