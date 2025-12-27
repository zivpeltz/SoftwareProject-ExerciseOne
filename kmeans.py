import sys


def calculate_distance(p,q): #p and q are arrays representing points
    sum_of_deltas = 0
    for i in range(len(p)):
        sum_of_deltas += (p[i] - q[i]) ** 2
    return sum_of_deltas**0.5


def is_float(value):
    try:
        float(value)
        return True
    except ValueError:
        return False


def parse_points():
    points_arr = []
    s = sys.stdin.readline()
    while s != "":
        if s == "\n":
            s = sys.stdin.readline()
            continue
        temp = s.strip()
        temp = temp.split(",")
        for i in range(len(temp)):
            if not is_float(temp[i]):
                print("An Error Has Occurred")
                raise SystemExit(1)
            temp[i] = float(temp[i])

        points_arr.append(temp)
        s = sys.stdin.readline()
    return points_arr

def update_centroid(cluster):
    dim = len(cluster[0])
    num_of_points = len(cluster)

    updated_centroid = [0 for i in range(dim)]

    for cord in range(dim):
        sum_of_cord = 0
        for point in range(num_of_points):
            sum_of_cord += cluster[point][cord]
        updated_centroid[cord] = sum_of_cord / num_of_points

    return updated_centroid

def find_closest_cluster(centroids, point): #recieves centroids and a point and returns the index of the closest centroid
    close_cluster_index=0
    distance=calculate_distance(centroids[0],point)
    for i in range(1,len(centroids)):
        temp_dis=calculate_distance(centroids[i],point)
        if temp_dis<distance:
            distance=temp_dis
            close_cluster_index=i
    return close_cluster_index

def print_centroids(centroids):
    for point in centroids:
        s = ""
        for cord in point:
            s = s + f"{cord:.4f}" + ","
        s = s[0:-1]
        print(s)



def cluster_handle(k , iter , points_arr):

    centroids = [0 for i in range(k)]
    clusters = [[] for i in range(k)]
    for i in range(k):
        centroids[i] = points_arr[i]
    for iteration in range(iter):

        temp_clusters = [[] for i in range(k)]
        for point in points_arr:
            index = find_closest_cluster(centroids,point)
            temp_clusters[index].append(point)

        clusters = temp_clusters
        convergence = True

        for i in range(k):
            if (len(clusters[i]) == 0):
                updated_centroid = points_arr[0]
            else:
                updated_centroid = update_centroid(clusters[i])

            for cord in range(len(updated_centroid)):
                if abs(centroids[i][cord]-updated_centroid[cord]) >= 0.001:
                    convergence = False

            centroids[i] = updated_centroid

        if convergence:
            break

    print_centroids(centroids)







def main():
    if len(sys.argv) == 1 or len(sys.argv) > 3:
        print("An Error Has Occurred")
        raise SystemExit(1)

    k = sys.argv[1]
    if not k.isdigit():
        print("Incorrect number of clusters!")
        raise SystemExit(1)

    k = int(k)

    if len(sys.argv)==3:
        iter = sys.argv[2]
        if not iter.isdigit():
            print("Incorrect maximum iteration!")
            raise SystemExit(1)
        iter = int(iter)
        if iter < 2 or iter > 799:
            print("Incorrect maximum iteration!")
            raise SystemExit(1)
    else:
        iter = 400

    points_arr = parse_points()


    N = len(points_arr)

    if N <= 1:
        print("An Error Has Occurred")
        raise SystemExit(1)

    if k < 2 or k > N-1:
        print("Incorrect number of clusters!")
        raise SystemExit(1)

    cluster_handle(k, iter, points_arr)
    
    

if __name__=="__main__":
    main()
