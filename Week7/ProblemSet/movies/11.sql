-- Finding CB id number
-- SELECT id FROM people WHERE name LIKE "Chadwick Boseman";

SELECT movies.title FROM people
JOIN stars on people.id = stars.person_id
JOIN movies on stars.movie_id = movies.id
JOIN ratings ON movies.id = ratings.movie_id
WHERE people.name ="Chadwick Boseman"
ORDER BY rating DESC
LIMIT 5;