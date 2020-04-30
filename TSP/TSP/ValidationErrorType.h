#pragma once

enum ValidationErrorType : int
{
    Success = 0,
    InvalidNode,
    NotEnoughNodes,
    DuplicateNodes,
    UnexistingEdge,
    UnexistingFinalEdge
};