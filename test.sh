valgrind --leak-check=full ./so_long ./maps/s
valgrind --leak-check=full ./so_long ./maps/no_extension
valgrind --leak-check=full ./so_long ./maps/empty1.ber
valgrind --leak-check=full ./so_long ./maps/empty2.ber
valgrind --leak-check=full ./so_long ./maps/not_rectangle1.ber
valgrind --leak-check=full ./so_long ./maps/not_rectangle2.ber
valgrind --leak-check=full ./so_long ./maps/not_rectangle3.ber
valgrind --leak-check=full ./so_long ./maps/bad_token.ber
valgrind --leak-check=full ./so_long ./maps/no_walls1.ber
valgrind --leak-check=full ./so_long ./maps/no_walls2.ber
valgrind --leak-check=full ./so_long ./maps/no_walls3.ber
valgrind --leak-check=full ./so_long ./maps/no_player.ber
valgrind --leak-check=full ./so_long ./maps/no_collectibles.ber
valgrind --leak-check=full ./so_long ./maps/no_exit.ber
valgrind --leak-check=full ./so_long ./maps/duplicate_player.ber
valgrind --leak-check=full ./so_long ./maps/duplicate_exit.ber
valgrind --leak-check=full ./so_long ./maps/map_not_reachable1.ber
valgrind --leak-check=full ./so_long ./maps/map_not_reachable2.ber
valgrind --leak-check=full ./so_long ./maps/map1.ber
