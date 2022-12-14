-- Finding the id of drake

-- SELECT id FROM artists WHERE name ="Drake";
--ID = 23
SELECT AVG(energy)
FROM songs
WHERE artist_id = (SELECT id FROM artists WHERE name = "Drake");