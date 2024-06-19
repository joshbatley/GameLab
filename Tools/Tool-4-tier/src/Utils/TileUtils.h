#pragma once

#include "Engine.h"

enum TileType {
    DEFAULT = 100,
    Water = 0,
    Sand = 1,
    Land = 2
};

const std::unordered_map<TileType, Vec::ivec2> TileTypes {
  {TileType::Water, {12 * 16, 11 * 16}},
  {TileType::Land, {18 * 16, 1 * 16}},
  {TileType::Sand, {12 * 16, 1 * 16}}};

struct RuleSet {
    Vec::ivec2 newSrc;
    std::vector<std::vector<int>> rule;
};

const std::vector<RuleSet> SandRules = {
  // Top
  {
    {11 * 16, 0 * 16},
    {{0, 0, 0},
     {0, 1, 1},
     {0, 1, 1}}},
  {{12 * 16, 0 * 16},
   {{0, 0, 0},
    {1, 1, 1},
    {1, 1, 1}}},
  {{13 * 16, 0 * 16},
   {{0, 0, 0},
    {1, 1, 0},
    {1, 1, 0}}},
  // Middle
  {
    {11 * 16, 1 * 16},
    {{0, 1, 1},
     {0, 1, 1},
     {0, 1, 1}}},
  {{12 * 16, 1 * 16},
   {{1, 1, 1},
    {1, 1, 1},
    {1, 1, 1}}},
  {{13 * 16, 1 * 16},
   {{1, 1, 0},
    {1, 1, 0},
    {1, 1, 0}}},
  // Bottom
  {
    {11 * 16, 2 * 16},
    {{0, 1, 1},
     {0, 1, 1},
     {0, 0, 0}}},
  {{12 * 16, 2 * 16},
   {{1, 1, 1},
    {1, 1, 1},
    {0, 0, 0}}},
  {{13 * 16, 2 * 16},
   {{1, 1, 0},
    {1, 1, 0},
    {0, 0, 0}}},
};


const std::vector<RuleSet> WaterRules = {
  // Top
  {
    {11 * 16, 10 * 16},
    {{1, 1, 1},
     {1, 0, 0},
     {1, 0, 0}}},
  {{12 * 16, 10 * 16},
   {{1, 1, 1},
    {0, 0, 0},
    {0, 0, 0}}},
  {{13 * 16, 10 * 16},
   {{1, 1, 1},
    {0, 0, 1},
    {0, 0, 1}}},
  {{12 * 16, 10 * 16},
   {{1, 1, 1},
    {0, 0, 0},
    {1, 1, 1}}},
  {{12 * 16, 10 * 16},
   {{1, 1, 1},
    {0, 0, 0},
    {2, 2, 2}}},
  // Middle
  {
    {11 * 16, 11 * 16},
    {{12, 0, 0},
     {1, 0, 0},
     {1, 0, 0}}},
  {{12 * 16, 11 * 16},
   {{0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}}},
  {{13 * 16, 11 * 16},
   {{0, 0, 1},
    {0, 0, 1},
    {0, 0, 1}}},
  // Bottom
  {
    {11 * 16, 12 * 16},
    {{1, 0, 0},
     {1, 0, 0},
     {1, 1, 1}}},
  {{12 * 16, 12 * 16},
   {{0, 0, 0},
    {0, 0, 0},
    {1, 1, 1}}},
  {{13 * 16, 12 * 16},
   {{0, 0, 1},
    {0, 0, 1},
    {1, 1, 1}}},

  // top
  {
    {11 * 16, 10 * 16},
    {{2, 2, 2},
     {2, 0, 0},
     {2, 0, 0}}},
  {{12 * 16, 10 * 16},
   {{2, 2, 2},
    {0, 0, 0},
    {0, 0, 0}}},
  {{13 * 16, 10 * 16},
   {{2, 2, 2},
    {0, 0, 2},
    {0, 0, 2}}},


  {{12 * 16, 10 * 16},
   {{2, 2, 2},
    {0, 0, 0},
    {2, 2, 2}}},

  {{12 * 16, 10 * 16},
   {{2, 2, 2},
    {0, 0, 0},
    {1, 1, 1}}},


  // Middle
  {
    {11 * 16, 11 * 16},
    {{12, 0, 0},
     {2, 0, 0},
     {2, 0, 0}}},
  {{12 * 16, 11 * 16},
   {{0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}}},
  {{13 * 16, 11 * 16},
   {{0, 0, 2},
    {0, 0, 2},
    {0, 0, 2}}},
  // Bottom
  {
    {11 * 16, 12 * 16},
    {{2, 0, 0},
     {2, 0, 0},
     {2, 2, 2}}},
  {{12 * 16, 12 * 16},
   {{0, 0, 0},
    {0, 0, 0},
    {2, 2, 2}}},
  {{13 * 16, 12 * 16},
   {{0, 0, 2},
    {0, 0, 2},
    {2, 2, 2}}},
};

const std::vector<RuleSet> LandRules = {
  // Top
  {
    {17 * 16, 0 * 16},
    {{1, 1, 1},
     {1, 2, 2},
     {1, 2, 2}}},
  {{18 * 16, 0 * 16},
   {{1, 1, 1},
    {2, 2, 2},
    {2, 2, 2}}},
  {{19 * 16, 0 * 16},
   {{1, 1, 1},
    {2, 2, 1},
    {2, 2, 1}}},
  // Middle
  {
    {17 * 16, 1 * 16},
    {{1, 2, 2},
     {1, 2, 2},
     {1, 2, 2}}},
  {{18 * 16, 1 * 16},
   {{2, 2, 2},
    {2, 2, 2},
    {2, 2, 2}}},
  {{19 * 16, 1 * 16},
   {{2, 2, 1},
    {2, 2, 1},
    {2, 2, 1}}},
  // Bottom
  {
    {17 * 16, 2 * 16},
    {{1, 2, 2},
     {1, 2, 2},
     {1, 1, 1}}},
  {{18 * 16, 2 * 16},
   {{2, 2, 2},
    {2, 2, 2},
    {1, 1, 1}}},
  {{19 * 16, 2 * 16},
   {{2, 2, 1},
    {2, 2, 1},
    {1, 1, 1}}},
  // Land to sand
  {{11 * 16, 5 * 16},
   {{0, 0, 0},
    {0, 2, 2},
    {0, 2, 2}}},
  {{12 * 16, 5 * 16},
   {{0, 0, 0},
    {2, 2, 2},
    {2, 2, 2}}},
  {{13 * 16, 5 * 16},
   {{0, 0, 0},
    {2, 2, 0},
    {2, 2, 0}}},
  // Middle
  {
    {11 * 16, 6 * 16},
    {{0, 2, 2},
     {0, 2, 2},
     {0, 2, 2}}},
  {{12 * 16, 6 * 16},
   {{2, 2, 2},
    {2, 2, 2},
    {2, 2, 2}}},
  {{13 * 16, 6 * 16},
   {{2, 2, 0},
    {2, 2, 0},
    {2, 2, 0}}},
  // Bottom
  {
    {11 * 16, 7 * 16},
    {{0, 2, 2},
     {0, 2, 2},
     {0, 0, 0}}},
  {{12 * 16, 7 * 16},
   {{2, 2, 2},
    {2, 2, 2},
    {0, 0, 0}}},
  {{13 * 16, 7 * 16},
   {{2, 2, 0},
    {2, 2, 0},
    {0, 0, 0}}},
};

const std::unordered_map<TileType, std::vector<RuleSet>>
  Rules = {{Water, WaterRules}, {Land, LandRules}, {Sand, SandRules}};