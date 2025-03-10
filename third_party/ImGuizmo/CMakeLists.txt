find_package(imgui REQUIRED)

add_library(ImGuizmo
        GraphEditor.cpp
        GraphEditor.h
        ImCurveEdit.cpp
        ImCurveEdit.h
        ImGradient.cpp
        ImGradient.h
        ImGuizmo.cpp
        ImGuizmo.h
        ImSequencer.h
        ImZoomSlider.h
)

target_link_libraries(ImGuizmo imgui::imgui)
target_include_directories(ImGuizmo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})