import random

# Define snakes and ladders
snakes_and_ladders = {
    23: 1, 21: 8, 19: 7,
    4: 17, 3: 22, 20: 29
}

# Initialize players and positions
players = ['Player1', 'Player2']
positions = {player: 0 for player in players}

# Game play function
def play_game():
    while True:
        for player in players:
            dice_value = int(input(f"{player}, Enter the upper face of the dice (1-6): "))
            print(f"{player} rolled a {dice_value}")

            # Update position
            new_position = positions[player] + dice_value
            if new_position > 30:
                print(f"{player} stays at {positions[player]} (roll exceeds 30)")
            else:
                positions[player] = new_position
                # Check for snakes or ladders
                if new_position in snakes_and_ladders:
                    old_position = positions[player]
                    positions[player] = snakes_and_ladders[new_position]
                    if positions[player] < old_position:
                        print(f"{player} encountered a snake!")
                    else:
                        print(f"{player} climbed a ladder!")

                print(f"{player} is now at {positions[player]}")

            # Check for win condition
            if positions[player] == 30:
                print(f"Congratulations, {player} wins!")
                return

# Start the game
play_game()
