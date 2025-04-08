import perfplot
import random
import string
from MySHA import sha256, sha512

def generate_random_string(size):
    """Generate a random string of the given size."""
    return ''.join(random.choices(string.ascii_letters + string.digits, k=size))

# Define the performance plot
perfplot.show(
    setup=lambda n: generate_random_string(n),  # Generate random input of size n
    kernels=[
        sha256,
        sha512,
    ],
    labels=["SHA-256", "SHA-512"],
    n_range=[2**i for i in range(5, 15)],  # Input sizes from 32 to 32768 bytes
    xlabel="Input size (bytes)",
    title="Performance Comparison: SHA-256 vs SHA-512",
    equality_check=None  # Skip equality check since outputs differ
)