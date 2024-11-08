import cv2
import pytesseract
import sqlite3
import math
import time

# Configure Tesseract if necessary
# pytesseract.pytesseract.tesseract_cmd = r'path_to_tesseract_executable'

# Constants
METER_RATE = 0.5
EARTH_RADIUS = 6371000  # Earth’s radius in meters

# GPS coordinates (mock data for testing; replace with actual GPS input in real usage)
lat1, lon1 = 0.0, 0.0  # Starting point coordinates
lat2, lon2 = 0.0, 0.0  # Updated coordinates

def recognize_text_from_image(image_path):
    # Image preprocessing and OCR
    image = cv2.imread(image_path)
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    gray = cv2.bilateralFilter(gray, 11, 17, 17)
    vehicle_number = pytesseract.image_to_string(gray, config='--psm 8').strip()
    return vehicle_number

def search_database(vehicle_number):
    conn = sqlite3.connect('vehicle_info.db')
    cursor = conn.cursor()
    cursor.execute("SELECT name, phone_number, account_details FROM vehicle_info WHERE vehicle_number = ?", (vehicle_number,))
    result = cursor.fetchone()
    conn.close()
    if result:
        return result  # Returns (name, phone, account)
    else:
        return None

def calculate_distance(lat1, lon1, lat2, lon2):
    delta_lat = math.radians(lat2 - lat1)
    delta_lon = math.radians(lon2 - lon1)
    a = math.sin(delta_lat / 2)**2 + math.cos(math.radians(lat1)) * math.cos(math.radians(lat2)) * math.sin(delta_lon / 2)**2
    c = 2 * math.atan2(math.sqrt(a), math.sqrt(1 - a))
    return EARTH_RADIUS * c  # Distance in meters

def gps_update_and_calculate():
    global lat1, lon1, lat2, lon2
    distance, charge = 0, 0

    # Mock GPS updates (replace with actual GPS data input in real usage)
    lat2, lon2 = 12.971598, 77.594566  # Example coordinates for testing
    time.sleep(1)  # Simulate GPS update delay

    if lat1 and lon1:
        distance = calculate_distance(lat1, lon1, lat2, lon2) / 1000  # Convert to km
        charge = distance * METER_RATE
    lat1, lon1 = lat2, lon2  # Update for the next calculation
    return distance, charge

# Main function
def main():
    image_path = 'vehicle_image.jpg'  # Replace with the path of the vehicle image
    vehicle_number = recognize_text_from_image(image_path)
    if vehicle_number:
        print(f"Detected Vehicle Number: {vehicle_number}")
        result = search_database(vehicle_number)
        if result:
            name, phone, account = result
            print(f"Owner: {name}, Phone: {phone}, Account: {account}")

            # Get GPS distance and charge
            distance, charge = gps_update_and_calculate()
            print(f"Distance: {distance:.2f} km")
            print(f"Charge: Rs.{charge:.2f}")
        else:
            print("Vehicle not found in database.")
    else:
        print("No vehicle number detected.")

main()






