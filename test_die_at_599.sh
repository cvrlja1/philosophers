#!/bin/bash

# Path to the program
PROGRAM="./philo"

# Test case parameters
params="199 599 200 200 5"

# Timeout for the 'no_death' case (in seconds)
TIMEOUT_DURATION=10

# Output file base name
OUTPUT_BASE="philo_test_death_around_599"

# Number of iterations
RUNS=100

# Loop to run the test 100 times
for ((i = 1; i <= RUNS; i++)); do
  OUTPUT_FILE="${OUTPUT_BASE}_run_${i}.txt"
  
  # Run the program with timeout for the 'no_death' case
  timeout $TIMEOUT_DURATION $PROGRAM $params > "$OUTPUT_FILE" &
  pid=$!
  wait $pid
  elapsed_time=$TIMEOUT_DURATION

  # Measure execution time for non-timeout cases
  if [[ $? -eq 0 ]]; then
    start_time=$(date +%s.%N)
    $PROGRAM $params > "$OUTPUT_FILE"
    end_time=$(date +%s.%N)
    elapsed_time=$(echo "$end_time - $start_time" | bc -l)
  fi

  # Validate output for 'death_around_599' case
  if grep -qE "59[0-9]|6[0-0][0-9] .* died" "$OUTPUT_FILE"; then
    echo "Run $i: Test passed. Death occurred within 589ms to 609ms."
  else
    # Test failed, save output to a failure file
    FAILURE_FILE="philo_test_death_around_599_failed_run_${i}.txt"
    echo "Run $i: Test failed. No death within 589ms to 609ms in 'death_around_599' case." > "$FAILURE_FILE"
    cat "$OUTPUT_FILE" >> "$FAILURE_FILE"
    echo "Run $i: Failure details saved to $FAILURE_FILE."
  fi

  # Clean up output files
  rm "$OUTPUT_FILE"
done

echo "All tests completed."
