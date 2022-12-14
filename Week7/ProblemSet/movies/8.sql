-- Nested query to find the ID of the toy story film
-- SELECT id FROM movies WHERE title = "Toy Story";

--Query to find the person_id for those that acted in Toy Story
-- SELECT person_id FROM stars WHERE movie_id = 114709;

SELECT name FROM people
JOIN stars on people.id = stars.person_id
JOIN movies on stars.movie_id = movies.id
WHERE movies.title = "Toy Story";


--In 8.sql,
--write a SQL query to list the names of all people who starred in Toy Story.
--Your query should output a table with a single column for the name of each person.
--You may assume that there is only one movie in the database with the title Toy Story.