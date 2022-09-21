
unsigned int ham_dist(const std::vector <int>& data, unsigned int offset1, unsigned int offset2)
{
    unsigned int answer = 0, size = (data.size() >> 1);
    for (unsigned int j = 0; j < size; j++) answer += (data[offset1 + j] != data[offset2 + j]);
    return answer;
}

int main(void)
{

    for (unsigned int i = 1; i < n; i++)
    {
        int d = ham_dist(numbers, 0, i);
        if (d > max_ham_dist) { answers.clear(); max_ham_dist = d; }
        if (d == max_ham_dist) answers.push_back(i);
    }

    std::cout << max_ham_dist << "\n";
    for (unsigned int i = 0; i < answers.size(); i++)
    {
        bool unique = true;
        for (unsigned int j = 0; j < i; j++)
        {
            if (ham_dist(numbers, answers[i], answers[j]) == 0) { unique = false; break; }
        }
        if (!unique) break;
        std::cout << numbers[answers[i]];
        for (unsigned int j = 1; j < n; j++) std::cout << " " << numbers[answers[i] + j];
        std::cout << "; " << answers[i] << "\n";
    }

    return 0;
}