#include "MatrixStack.h"

MatrixStack::MatrixStack()
{
    m_Matrices.push_back(glm::mat4()); // add identity matrix on top of stack
}

void MatrixStack::Clear()
{
    m_Matrices.clear();
    m_Matrices.push_back(glm::mat4()); // add identity matrix on top of stack
}

void MatrixStack::Push(glm::mat4 matrix)
{
    m_Matrices.push_back(matrix);
}

glm::mat4 MatrixStack::Pop()
{
    if (Count() > 0)
    {
        glm::mat4 matrix = GetTopMatrix();
        m_Matrices.pop_back();
        return matrix;
    }
    else
        return glm::mat4();
}

const glm::mat4& MatrixStack::GetTopMatrix() const
{
    return m_Matrices[Count() - 1];
}

unsigned int MatrixStack::Count() const 
{
    return m_Matrices.size();
}