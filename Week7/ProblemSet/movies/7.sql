SELECT title,rating FROM movies
JOIN ratings on movies.id = ratings.movie_id
WHERE movies.year = 2010
ORDER BY 2 DESC, 1;
-- The one is to order the same ratings by alphabet. the left number comes first followed by a second number